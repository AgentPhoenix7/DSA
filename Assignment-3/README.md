# 📘 Assignment 3 – DSA

This folder contains solutions to **Assignment 3** problems from the DSA course.

---

## 📝 Problems Covered

### Problem 1 – Implementing a Stack
#### (a) Stack using Array  
- **Description**:  
  Implement a stack using an **array** with `PUSH()` and `POP()` operations.  
  Assume that the number of elements never exceeds 100,000.  
- **Approach**:  
  - Maintain an array with a `top` pointer.  
  - Push increments `top`, Pop decrements `top`.  
- **Complexity**:  
  - PUSH: **O(1)**  
  - POP: **O(1)**  
- **Code**: [p01a.c](./p01a.c)

#### (b) Stack using Linked List  
- **Description**:  
  Implement a stack using a **linked list** with `PUSH()` and `POP()`.  
- **Approach**:  
  - Dynamically create nodes with `malloc`.  
  - Push inserts at the head, Pop deletes from the head.  
- **Complexity**:  
  - PUSH: **O(1)**  
  - POP: **O(1)**  
- **Code**: [p01b.c](./p01b.c)

---

### Problem 2 – Implementing a Queue using Linked List
- **Description**:  
  Implement a queue using a **linked list** with the following operations:  
  - Enqueue: Add element to rear.  
  - Dequeue: Remove element from front.  
  - Peek: Return front element.  
  - isEmpty: Check if queue is empty.  
  - Size: Return number of elements.  
- **Approach**:  
  - Maintain `front` and `rear` pointers.  
  - Update pointers correctly for enqueue/dequeue.  
- **Complexity**:  
  - Enqueue: **O(1)**  
  - Dequeue: **O(1)**  
  - Peek: **O(1)**  
- **Code**: [p02.c](./p02.c)

---

### Problem 3 – Sparse Matrix Operations
#### (a) Sparse to Compact Representation  
- **Description**: Convert a sparse matrix to its **compact form**.  
- **Approach**: Store only `(row, col, value)` of non-zero entries.  
- **Code**: [p03a.c](./p03a.c)

#### (b) Addition of Two Compact Matrices  
- **Description**: Add two matrices represented in compact form.  
- **Approach**: Merge `(row, col)` pairs, summing values when coordinates match.  
- **Code**: [p03b.c](./p03b.c)

#### (c) Multiplication of Two Compact Matrices  
- **Description**: Multiply two matrices represented in compact form.  
- **Approach**:  
  - Compare `col` of A with `row` of B.  
  - Multiply matching values and accumulate results at `(row, col)`.  
- **Code**: [p03c.c](./p03c.c)

#### (d) File-based Sparse Matrix Addition and Multiplication  
- **Description**:  
  - Read two matrices from `matrix1.txt` and `matrix2.txt`.  
  - Convert to compact form.  
  - Perform addition and multiplication.  
- **Code**: [p03d.c](./p03d.c)  
- **Input Files**: [matrix1.txt](./matrix1.txt), [matrix2.txt](./matrix2.txt)

---

## ▶️ Sample Run

### Stack (Array)
```bash
gcc p01a.c -o stack_array
./stack_array
```

```
Stack Menu
1. PUSH
2. POP
3. Display Stack
4. Exit
```

### Stack (Linked List)

```bash
gcc p01b.c -o stack_ll
./stack_ll
```

### Queue

```bash
gcc p02.c -o queue
./queue
```

### Sparse Matrix

```bash
gcc p03a.c -o compact
./compact
```

### File-based Sparse Matrix

```bash
gcc p03d.c -o file_sparse
./file_sparse
```

**Input (matrix1.txt):**

```
3 3
8 0 0
9 0 0
0 5 7
```

**Input (matrix2.txt):**

```
3 3
8 0 1
0 5 8
9 0 0
```

**Output Example (Addition & Multiplication):**

```
Resultant Compact Matrix (A + B):
Row    Col    Value
0      0      16
0      2      1
1      0      18
2      1      10
2      2      15

Resultant Compact Matrix (A x B):
Row    Col    Value
0      0      64
1      0      72
2      1      25
2      2      40
```

---

## 📊 Learning Outcome

* Understood **stack and queue fundamentals** (array vs linked list).
* Implemented **basic operations** on linear data structures.
* Learned **sparse matrix representation** and performed **addition/multiplication** efficiently.
* Practiced working with **file input/output** in C.

---
