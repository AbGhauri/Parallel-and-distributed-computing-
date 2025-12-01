import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';

const PROTO_PATH = path.join(__dirname, 'calculator.proto');
const SERVER_ADDRESS = 'localhost:50051';

// Load proto file
const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
  keepCase: true,
  longs: String,
  enums: String,
  defaults: true,
  oneofs: true,
});

const calculatorProto = grpc.loadPackageDefinition(packageDefinition).calculator as any;

// Create client
const client = new calculatorProto.Calculator(
  SERVER_ADDRESS,
  grpc.credentials.createInsecure()
);

// Type definitions
interface CalculatorRequest {
  a: number;
  b: number;
}

interface CalculatorResponse {
  result: number;
  operation: string;
}

// Helper function to call RPC methods
function callMethod(methodName: string, a: number, b: number): Promise<CalculatorResponse> {
  return new Promise((resolve, reject) => {
    client[methodName]({ a, b }, (error: grpc.ServiceError | null, response: CalculatorResponse) => {
      if (error) {
        reject(error);
      } else {
        resolve(response);
      }
    });
  });
}

// Run tests
async function runTests() {
  console.log('🧪 Testing gRPC Calculator Service...\n');

  try {
    const addResult = await callMethod('Add', 10, 5);
    console.log(`Add: 10 and 5 = ${addResult.result}`);

    const subtractResult = await callMethod('Subtract', 10, 5);
    console.log(`Subtract: 10 and 5 = ${subtractResult.result}`);

    const multiplyResult = await callMethod('Multiply', 10, 5);
    console.log(`Multiply: 10 and 5 = ${multiplyResult.result}`);

    const divideResult = await callMethod('Divide', 10, 5);
    console.log(`Divide: 10 and 5 = ${divideResult.result}`);

    console.log('\n✅ All tests completed!');
  } catch (error) {
    console.error('❌ Error:', error);
  } finally {
    client.close();
  }
}

runTests();