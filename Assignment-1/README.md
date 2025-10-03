# 📘 Assignment 1 – DSA

This folder contains solutions to **Assignment 1** problems from the DSA course.

---

## 📝 Problems Covered

### Problem 1 – Store Integer Data in an Array  
- **Description**:  
  Write a program which will accept some integer data from the user input (or from a file) and store the data in an array.  
  The array will end with the value **`0`**.  
- **Approach**:  
  - Read integers one by one.  
  - Stop input when sentinel value `0` is encountered.  
  - Store all values in an array, then display them.  
- **Complexity**:  
  - Input: **O(n)**  
  - Output: **O(n)**  
- **Code**: [p01.c](./p01.c)

---

### Problem 2 – Extended Array Operations  
- **Description**:  
  Update the program with the following functions:  
  a) Insert a new data **after** a given data in the array.  
  b) Insert a new data **before** a given data in the array.  
  c) Delete a given data from the array.  
  d) Insert a data exactly at the **n-th position** in the array.  
  e) Find the **middle data** of the array.  
  f) Get the **n-th data from the end** of the array.  
- **Approach**:  
  - Perform **array shifting** to insert or delete.  
  - For middle element:  
    - If size is odd → single middle element.  
    - If size is even → two middle elements.  
  - For n-th from end: calculate index as `size - n`.  
- **Complexity**:  
  - Insert/Delete: **O(n)** (due to shifting elements).  
  - Find middle: **O(1)**  
  - n-th from end: **O(1)**  
- **Code**: [p02.c](./p02.c)

---

## ▶️ Sample Run

### For Problem 1

```bash
gcc p01.c -o p01
./p01
```

**Input:**

```
Enter integers (End with 0):
5 7 3 0
```

**Output:**

```
The Entered Array Is:
5 7 3
```

---

### For Problem 2

```bash
gcc p02.c -o p02
./p02
```

**Input/Output Example:**

```
Enter integers (End with 0):
10 20 30 40 0

Menu:
1. Insert after a value
2. Insert before a value
3. Delete a value
4. Insert at n-th position
5. Find middle data
6. Get n-th data from the end
7. Print array
8. Exit
Enter your choice: 5
Middle data: 20 and 30
```

---

## 📊 Learning Outcome

* Learned how to **store and manipulate arrays** in C.
* Understood **array-based insertion, deletion, and shifting operations**.
* Analyzed the **time complexity** of array operations.
* Gained practice with **menu-driven interactive programs** in C.

---
