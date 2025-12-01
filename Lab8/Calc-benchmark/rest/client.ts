// REST Client - Test the calculator service
const BASE_URL = 'http://localhost:3000';

interface CalculatorRequest {
  a: number;
  b: number;
}

interface CalculatorResponse {
  result: number;
  operation: string;
}

async function testOperation(endpoint: string, a: number, b: number) {
  try {
    const response = await fetch(`${BASE_URL}${endpoint}`, {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ a, b } as CalculatorRequest),
    });

    const data = await response.json() as CalculatorResponse;
    console.log(`${endpoint}: ${a} and ${b} = ${data.result}`);
    return data;
  } catch (error) {
    console.error(`Error testing ${endpoint}:`, error);
  }
}

async function runTests() {
  console.log('🧪 Testing REST Calculator Service...\n');

  await testOperation('/add', 10, 5);
  await testOperation('/subtract', 10, 5);
  await testOperation('/multiply', 10, 5);
  await testOperation('/divide', 10, 5);
  
  console.log('\n✅ All tests completed!');
}

// Run tests
runTests();