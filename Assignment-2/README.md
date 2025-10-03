# 📘 Assignment 2 – DSA

This folder contains solutions to **Assignment 2** problems from the DSA course.

---

## 📝 Problems Covered

### Problem 1 – Store Integer Data in a Linked List  
- **Description**:  
  Write a program which will accept some integer data from the user input (or from a file) and store the data in a **linked list**.  
  The input ends when the user enters **`-1`**.  
- **Approach**:  
  - Use a singly linked list.  
  - Dynamically create nodes with `malloc`.  
  - Append new nodes to the end of the list.  
  - Traverse and display the list.  
- **Complexity**:  
  - Insertion at end: **O(n)** (due to traversal).  
  - Display: **O(n)**  
- **Code**: [p01.c](./p01.c)

---

### Problem 2 – Extended Linked List Operations  
- **Description**:  
  Update the program with the following functions:  
  a) Insert a new data **after** a given data.  
  b) Insert a new data **before** a given data.  
  c) Delete a given data.  
  d) Insert a data exactly at the **n-th position**.  
  e) Find the **middle data** of the list.  
  f) Get the **n-th data from the end** of the list.  
- **Approach**:  
  - **Insertions/Deletions**: Adjust pointers carefully while creating/freeing nodes.  
  - **Find middle**: Use the **slow/fast pointer method**.  
  - **n-th from end**: Use two pointers with an offset of `n`.  
- **Complexity**:  
  - Insert/Delete: **O(n)** (linear traversal).  
  - Find middle: **O(n)** (two-pointer traversal).  
  - n-th from end: **O(n)**  
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
Input integers (-1 to stop):
10 20 30 -1
```

**Output:**

```
Linked List: 10 20 30
```

---

### For Problem 2

```bash
gcc p02.c -o p02
./p02
```

**Example Interaction:**

```
Menu:
1. Append value(s)
2. Display list
3. Insert after a value
4. Insert before a value
5. Delete a value
6. Insert at n-th position
7. Find middle value
8. Get n-th from end
9. Clear list
0. Exit

Enter choice: 1
Input integers (-1 to stop):
5 15 25 -1

Enter choice: 7
Middle value: 15

Enter choice: 8
n (from end): 2
2-th from end: 15
```

---

## 📊 Learning Outcome

* Learned how to **dynamically create and manage linked lists** in C.
* Understood **insertion and deletion operations** in a linked list.
* Applied **two-pointer techniques** (fast/slow for middle, offset for n-th from end).
* Practiced **memory management** using `malloc` and `free`.

---
