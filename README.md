# Multithreaded Log Parser (C++20)

A high-performance, multithreaded log parsing pipeline built in **Modern C++ (C++20)** using a **producer–consumer architecture**.  
The system efficiently parses Apache-style access logs with clean concurrency, backpressure, and graceful shutdown semantics.

---

## 🚀 Features

- **Producer–Consumer Pipeline**
  - Single log reader (producer)
  - Multiple log parser threads (consumers)

- **ThreadPool-based Execution**
  - Fixed-size worker pool
  - Clean lifecycle management

- **Thread-Safe Blocking Queue**
  - Bounded queue for natural backpressure
  - No busy waiting
  - Multiple producers / consumers supported

- **Lock-Free Parsing Path**
  - Each parser thread stores results locally
  - No shared global state during parsing

- **Graceful Shutdown**
  - Reader owns queue closure
  - Parsers exit naturally once work is complete

- **Final Aggregation & Output**
  - Single-threaded aggregation
  - Parsed logs written to CSV

---

## 🧱 Architecture Diagram

<img width="1027" height="717" alt="image" src="https://github.com/user-attachments/assets/5787b892-fb2a-4a74-b8ce-4402a24311fc" />
