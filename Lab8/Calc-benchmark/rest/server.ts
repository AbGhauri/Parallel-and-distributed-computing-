import express, { Request, Response } from 'express';
import bodyParser from 'body-parser';
import cors from 'cors';

const app = express();
const PORT = 3000;

// Middleware
app.use(bodyParser.json());
app.use(cors());

// Request/Response interfaces
interface CalculatorRequest {
  a: number;
  b: number;
}

interface CalculatorResponse {
  result: number;
  operation: string;
}

// Calculator operations
app.post('/add', (req: Request<{}, {}, CalculatorRequest>, res: Response<CalculatorResponse>) => {
  const { a, b } = req.body;
  const result = a + b;
  res.json({ result, operation: 'addition' });
});

app.post('/subtract', (req: Request<{}, {}, CalculatorRequest>, res: Response<CalculatorResponse>) => {
  const { a, b } = req.body;
  const result = a - b;
  res.json({ result, operation: 'subtraction' });
});

app.post('/multiply', (req: Request<{}, {}, CalculatorRequest>, res: Response<CalculatorResponse>) => {
  const { a, b } = req.body;
  const result = a * b;
  res.json({ result, operation: 'multiplication' });
});

app.post('/divide', (req: Request<{}, {}, CalculatorRequest>, res: Response<CalculatorResponse>) => {
  const { a, b } = req.body;
  if (b === 0) {
    res.status(400).json({ result: 0, operation: 'division error - divide by zero' } as any);
    return;
  }
  const result = a / b;
  res.json({ result, operation: 'division' });
});

// Health check endpoint
app.get('/health', (req: Request, res: Response) => {
  res.json({ status: 'REST Calculator Service is running', port: PORT });
});

// Start server
app.listen(PORT, () => {
  console.log(` REST Calculator Server running on http://localhost:${PORT}`);
  console.log(` Available endpoints:`);
  console.log(`   POST /add      - Add two numbers`);
  console.log(`   POST /subtract - Subtract two numbers`);
  console.log(`   POST /multiply - Multiply two numbers`);
  console.log(`   POST /divide   - Divide two numbers`);
  console.log(`   GET  /health   - Check server status`);
});