# 🧮 Command-Based Calculator (C++)

This is a command-line calculator written in modern C++ that allows users to input and evaluate arithmetic operations using natural command syntax like:

```
add 10 5
divide 42 6
multiply 3 7
```

The program parses the user input into three parts:
- A command keyword (`add`, `subtract`, `multiply`, `divide`, `quit`)
- The first operand
- The second operand

It then performs the appropriate operation and prints the result in a clean, readable format.

---

## ✅ Features

- Simple natural-language-style input
- Supports addition, subtraction, multiplication, division
- Case-insensitive commands (`ADD`, `add`, `Add`, etc.)
- Float and integer operand support
- Clear input format guidance and helpful error messages
- Retry limit enforcement for invalid inputs
- Graceful exit with the `quit` command
- Clean, modular code structure with full input validation

---

## 📦 Example Usage

```
<--------------------------------------------------------------------------------->
Format of input is <command> <operand1> <operand2>
Example: add 100 50
<--------------------------------------------------------------------------------->
Enter "Quit", to exit!
<--------------------------------------------------------------------------------->

Enter the command : divide 42 6

===================================================================================
The result of the "divide" operation is: 7
===================================================================================
```

---

## 🛠️ Build Instructions

### Prerequisites

- A C++17-compatible compiler (GCC, Clang, MSVC, etc.)

### Compile & Run (using g++)

```
g++ -std=c++17 -o CommandCalculator main.cpp
./CommandCalculator
```

---

## 📂 File Structure

```
.
├── main.cpp          # Source file containing the command-based calculator logic
└── README.md         # Project documentation
```

---

## ✨ Implementation Highlights

- Stream parsing using `istringstream` for input tokenization
- Input validation with custom error messages for incorrect formats
- Internal normalization with string-to-uppercase conversion
- Flexible access to operands and command via `std::map`
- Efficient memory use with `emplace` instead of `insert`
- End-of-stream handling to prevent overflow or trailing token errors

---

## 💡 Future Improvements

- [ ] Add more operations: `mod`, `pow`, `sqrt`, etc.
- [ ] Use a command dispatcher: `unordered_map<string, function<double(double, double)>>`
- [ ] Store operands and commands in a typed struct
- [ ] Support input from files or stdin redirection
- [ ] Add unit testing (using Catch2 or doctest)
- [ ] Refactor into reusable CLI engine or framework

---

## 👩‍💻 Author

**Biju**  
Command-line minimalist. Backend enthusiast. Framework nerd.  
This project is part of a broader exploration into systems-level programming and modern C++ tooling.

---

## 📝 License

This project is open for learning, sharing, and reuse.  
No restrictions — just drop a credit if you find it helpful. ❤️