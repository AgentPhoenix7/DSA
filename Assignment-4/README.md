# 📘 Assignment 4 – DSA

This folder contains solutions to **Assignment 4** problems from the DSA course.

---

## 📝 Problems Covered

### Problem 1 – Prime Divisors using Stack (Linked List)
- **Description**:  
  Write a program to read an integer and print its **prime divisors** in ascending order, using a stack implemented with a linked list.  
- **Approach**:  
  - Traverse all numbers from `n` down to `2`.  
  - Check if divisor is prime, push onto stack.  
  - Pop all elements to print divisors in ascending order.  
- **Complexity**:  
  - Prime check: **O(√n)**  
  - Divisor collection: **O(n)**  
- **Code**: [p01.c](./p01.c)

---

### Problem 2 – Balanced Parentheses using Stack
- **Description**:  
  Examine whether the pairs of parentheses `"()"`, `"[]"`, `"{}"` in an expression are balanced.  
- **Examples**:  
  - Input: `(){(([]))}` → Output: Balanced  
  - Input: `()(([]))}` → Output: Unbalanced  
- **Approach**:  
  - Push opening brackets onto stack.  
  - On encountering a closing bracket, pop and check for matching pair.  
- **Complexity**:  
  - **O(n)** (linear scan of expression).  
- **Code**: [p02.c](./p02.c)

---

### Problem 3 – Polish Notation Calculator (File Input)
- **Description**:  
  Implement a **Polish Notation (Prefix) calculator** that reads an expression from a file and displays the result.  
- **Input File**: [input.txt](./input.txt)  
```
+ 3 * 5 6
- 10 4
* + 2 3 - 10 5
/ 9 0
```

- **Approach**:  
  - Tokenize expression line by line.
  - Process tokens right-to-left using a stack.
  - Perform arithmetic operations.
  - Handle division by zero & invalid expressions.  
- **Complexity**:
    - Evaluation: **O(n)** per expression.  
- **Code**: [p03.c](./p03.c)

---

### Problem 4 – Queue-based String Pattern Checking

#### (a) Form `w#w`
- **Description**: Check if a string is of the form `w#w`, where `w` is alphanumeric.  
- **Example**: `abc#abc` → YES  
- **Code**: [p04a.c](./p04a.c)

#### (b) Form `ww`
- **Description**: Check if a string is of the form `ww`, where `w` is alphanumeric.  
- **Example**: `abcabc` → YES  
- **Code**: [p04b.c](./p04b.c)

#### (c) Form `w#w'`
- **Description**: Check if a string is of the form `w#w'`, where `w'` is the **reverse** of `w`.  
- **Example**: `abc#cba` → YES  
- **Code**: [p04c.c](./p04c.c)

- **Approach (for all three)**:
    - Use **queue ADT** for storing characters.
    - Compare characters according to required format.  
- **Complexity**:
    - Linear in string length → **O(n)**  

---

## ▶️ Sample Run

### Prime Divisors
```bash
gcc p01.c -o prime_divisors
./prime_divisors
```

**Input:**

```
Enter an integer: 60
```

**Output:**

```
Prime divisors: 2 3 5
```

---

### Balanced Parentheses

```bash
gcc p02.c -o parentheses
./parentheses
```

**Output:**

```
Expression: (){(([]))} is Balanced.
Expression: ((([]))} is Unbalanced.
```

---

### Polish Notation Calculator

```bash
gcc p03.c -o polish
./polish input.txt
```

**Output:**

```
Line 1 Result: 33
Line 2 Result: 6
Line 3 Result: 25
Line 4: Error: Division by zero.
```

---

### String Format Check

```bash
gcc p04a.c -o w_hash_w
./w_hash_w
```

**Input:** `abc#abc`
**Output:** `YES: The string is of the form w#w`

```bash
gcc p04b.c -o ww
./ww
```

**Input:** `xyzxyz`
**Output:** `YES: The string is of the form ww`

```bash
gcc p04c.c -o w_hash_rev_w
./w_hash_rev_w
```

**Input:** `test#tset`
**Output:** `YES: The string is of the form w#w'`

---

## 📊 Learning Outcome

* Strengthened understanding of **stack and queue ADTs**.
* Applied stacks for solving **prime factorization**, **parenthesis matching**, and **expression evaluation**.
* Applied queues for **string pattern validation problems**.
* Gained experience with **file input/output** and error handling in C.

---
