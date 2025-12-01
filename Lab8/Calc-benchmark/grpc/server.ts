import * as grpc from '@grpc/grpc-js';
import * as protoLoader from '@grpc/proto-loader';
import path from 'path';

const PROTO_PATH = path.join(__dirname, 'calculator.proto');
const PORT = '0.0.0.0:50051';

// Load proto file
const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
  keepCase: true,
  longs: String,
  enums: String,
  defaults: true,
  oneofs: true,
});

const calculatorProto = grpc.loadPackageDefinition(packageDefinition).calculator as any;

// Type definitions
interface CalculatorRequest {
  a: number;
  b: number;
}

interface CalculatorResponse {
  result: number;
  operation: string;
}

// gRPC service implementations
const add = (call: grpc.ServerUnaryCall<CalculatorRequest, CalculatorResponse>, callback: grpc.sendUnaryData<CalculatorResponse>) => {
  const { a, b } = call.request;
  const result = a + b;
  callback(null, { result, operation: 'addition' });
};

const subtract = (call: grpc.ServerUnaryCall<CalculatorRequest, CalculatorResponse>, callback: grpc.sendUnaryData<CalculatorResponse>) => {
  const { a, b } = call.request;
  const result = a - b;
  callback(null, { result, operation: 'subtraction' });
};

const multiply = (call: grpc.ServerUnaryCall<CalculatorRequest, CalculatorResponse>, callback: grpc.sendUnaryData<CalculatorResponse>) => {
  const { a, b } = call.request;
  const result = a * b;
  callback(null, { result, operation: 'multiplication' });
};

const divide = (call: grpc.ServerUnaryCall<CalculatorRequest, CalculatorResponse>, callback: grpc.sendUnaryData<CalculatorResponse>) => {
  const { a, b } = call.request;
  if (b === 0) {
    callback({
      code: grpc.status.INVALID_ARGUMENT,
      message: 'Division by zero',
    } as grpc.ServiceError);
    return;
  }
  const result = a / b;
  callback(null, { result, operation: 'division' });
};

// Create and start gRPC server
function main() {
  const server = new grpc.Server();
  
  server.addService(calculatorProto.Calculator.service, {
    Add: add,
    Subtract: subtract,
    Multiply: multiply,
    Divide: divide,
  });

  server.bindAsync(PORT, grpc.ServerCredentials.createInsecure(), (err, port) => {
    if (err) {
      console.error('Failed to start gRPC server:', err);
      return;
    }
    console.log(`✅ gRPC Calculator Server running on ${PORT}`);
    console.log(`📊 Available RPC methods:`);
    console.log(`   Add      - Add two numbers`);
    console.log(`   Subtract - Subtract two numbers`);
    console.log(`   Multiply - Multiply two numbers`);
    console.log(`   Divide   - Divide two numbers`);
  });
}

main();