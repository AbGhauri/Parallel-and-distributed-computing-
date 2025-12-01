// @ts-ignore: no type definitions for 'autocannon'
import autocannon from 'autocannon';
import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';
import fs from 'fs';

// Configuration
const DURATION = 10; // seconds
const CONNECTIONS = 10;
const PIPELINING = 1;

// REST endpoints
const REST_URL = 'http://localhost:3000';

// gRPC setup
const PROTO_PATH = path.join(__dirname, '../grpc/calculator.proto');
const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
  keepCase: true,
  longs: String,
  enums: String,
  defaults: true,
  oneofs: true,
});
const calculatorProto = grpc.loadPackageDefinition(packageDefinition).calculator as any;

interface BenchmarkResult {
  service: string;
  operation: string;
  latency: {
    mean: number;
    p50: number;
    p95: number;
    p99: number;
  };
  throughput: number;
  requests: number;
  errors: number;
  duration: number;
}

// Benchmark REST endpoint
async function benchmarkREST(endpoint: string, operation: string): Promise<BenchmarkResult> {
  console.log(`\n📊 Benchmarking REST ${operation}...`);
  
  const result = await autocannon({
    url: `${REST_URL}${endpoint}`,
    connections: CONNECTIONS,
    pipelining: PIPELINING,
    duration: DURATION,
    method: 'POST',
    headers: {
      'content-type': 'application/json',
    },
    body: JSON.stringify({ a: 10, b: 5 }),
  });

  return {
    service: 'REST',
    operation,
    latency: {
      mean: result.latency.mean,
      p50: result.latency.p50,
      p95: result.latency.p95,
      p99: result.latency.p99,
    },
    throughput: result.requests.average,
    requests: result.requests.total,
    errors: result.errors,
    duration: result.duration,
  };
}

// Benchmark gRPC method
async function benchmarkGRPC(method: string, operation: string): Promise<BenchmarkResult> {
  console.log(`\n📊 Benchmarking gRPC ${operation}...`);

  const client = new calculatorProto.Calculator(
    'localhost:50051',
    grpc.credentials.createInsecure()
  );

  const startTime = Date.now();
  let completed = 0;
  let errors = 0;
  const latencies: number[] = [];

  return new Promise((resolve) => {
    const endTime = startTime + DURATION * 1000;

    const makeRequest = () => {
      if (Date.now() >= endTime) {
        client.close();
        
        const duration = (Date.now() - startTime) / 1000;
        const sortedLatencies = latencies.sort((a, b) => a - b);
        const len = sortedLatencies.length;

        // Safe index
        const idx = (p: number) => sortedLatencies[Math.floor(len * p)] ?? 0;

        resolve({
          service: 'gRPC',
          operation,
          latency: {
            mean: len ? latencies.reduce((a, b) => a + b, 0) / len : 0,
            p50: idx(0.5),
            p95: idx(0.95),
            p99: idx(0.99),
          },
          throughput: completed / duration,
          requests: completed,
          errors,
          duration,
        });
        return;
      }

      const reqStart = Date.now();
      client[method]({ a: 10, b: 5 }, (error: any) => {
        const reqEnd = Date.now();
        latencies.push(reqEnd - reqStart);
        
        if (error) {
          errors++;
        } else {
          completed++;
        }
        
        makeRequest();
      });
    };

    // Start concurrent requests
    for (let i = 0; i < CONNECTIONS; i++) {
      makeRequest();
    }
  });
}

// Calculate payload sizes
function calculatePayloadSizes() {
  console.log('\n📦 Calculating Payload Sizes...\n');

  // REST payload
  const restRequest = JSON.stringify({ a: 10, b: 5 });
  const restResponse = JSON.stringify({ result: 15, operation: 'addition' });
  const restTotal = Buffer.byteLength(restRequest) + Buffer.byteLength(restResponse);

  console.log('REST Payloads:');
  console.log(`  Request:  ${Buffer.byteLength(restRequest)} bytes`);
  console.log(`  Response: ${Buffer.byteLength(restResponse)} bytes`);
  console.log(`  Total:    ${restTotal} bytes`);

  // gRPC payload (Protocol Buffers are binary and much smaller)
  const grpcRequest = 8 + 8 + 2;
  const grpcResponse = 8 + 10 + 2;
  const grpcTotal = grpcRequest + grpcResponse;

  console.log('\ngRPC Payloads (Protocol Buffers):');
  console.log(`  Request:  ~${grpcRequest} bytes`);
  console.log(`  Response: ~${grpcResponse} bytes`);
  console.log(`  Total:    ~${grpcTotal} bytes`);

  console.log(`\n💾 Payload Size Difference: REST is ${(restTotal / grpcTotal).toFixed(2)}x larger\n`);

  return {
    rest: { request: Buffer.byteLength(restRequest), response: Buffer.byteLength(restResponse), total: restTotal },
    grpc: { request: grpcRequest, response: grpcResponse, total: grpcTotal },
  };
}

// Run all benchmarks
async function runBenchmarks() {
  console.log('🚀 Starting Benchmarks...');
  console.log(`⏱️  Duration: ${DURATION} seconds per test`);
  console.log(`🔌 Connections: ${CONNECTIONS}\n`);

  const results: BenchmarkResult[] = [];

  // REST
  results.push(await benchmarkREST('/add', 'Add'));
  results.push(await benchmarkREST('/subtract', 'Subtract'));
  results.push(await benchmarkREST('/multiply', 'Multiply'));
  results.push(await benchmarkREST('/divide', 'Divide'));

  // gRPC
  results.push(await benchmarkGRPC('Add', 'Add'));
  results.push(await benchmarkGRPC('Subtract', 'Subtract'));
  results.push(await benchmarkGRPC('Multiply', 'Multiply'));
  results.push(await benchmarkGRPC('Divide', 'Divide'));

  const payloads = calculatePayloadSizes();

  printSummary(results);

  saveResults(results, payloads);
}

// Print summary
function printSummary(results: BenchmarkResult[]) {
  const fmt = (n: number | undefined) => (n ?? 0).toFixed(2);

  console.log('\n' + '='.repeat(80));
  console.log('📈 BENCHMARK RESULTS SUMMARY');
  console.log('='.repeat(80));

  console.log('\n🏃 Throughput (requests/second):');
  console.log('-'.repeat(50));
  results.forEach((r) => {
    console.log(`${r.service.padEnd(8)} ${r.operation.padEnd(12)} ${fmt(r.throughput).padStart(10)} req/s`);
  });

  console.log('\n⏱️  Mean Latency (milliseconds):');
  console.log('-'.repeat(50));
  results.forEach((r) => {
    console.log(`${r.service.padEnd(8)} ${r.operation.padEnd(12)} ${fmt(r.latency.mean).padStart(10)} ms`);
  });

  console.log('\n📊 Latency Percentiles (milliseconds):');
  console.log('-'.repeat(70));
  console.log('Service  Operation    P50        P95        P99');
  console.log('-'.repeat(70));
  results.forEach((r) => {
    console.log(
      `${r.service.padEnd(8)} ${r.operation.padEnd(12)} ` +
      `${fmt(r.latency.p50).padStart(8)} ` +
      `${fmt(r.latency.p95).padStart(8)} ` +
      `${fmt(r.latency.p99).padStart(8)}`
    );
  });

  console.log('\n' + '='.repeat(80));
}

// Save results to file
function saveResults(results: BenchmarkResult[], payloads: any) {
  const output = {
    timestamp: new Date().toISOString(),
    configuration: {
      duration: DURATION,
      connections: CONNECTIONS,
      pipelining: PIPELINING,
    },
    payloads,
    results,
  };

  const filename = `results/benchmark_${Date.now()}.json`;
  fs.writeFileSync(filename, JSON.stringify(output, null, 2));
  console.log(`\n💾 Results saved to: ${filename}\n`);
}

// Run benchmarks
runBenchmarks().catch(console.error);
