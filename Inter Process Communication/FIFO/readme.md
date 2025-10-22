# 🧠 Inter-Process Communication using FIFOs (Named Pipes)

This project demonstrates two-way communication between two independent processes using named pipes (FIFOs) in a Linux/Unix environment.

It consists of two C programs, `process1.c` and `process2.c`, which communicate by passing data through two separate FIFO files.

## 🧩 Overview

#### Process 1 (Sender/Client):
* Takes sentences as input from the user.
* Sends the input to Process 2 through a dedicated FIFO.
* Waits for a response from Process 2 and displays the processed result.

#### Process 2 (Receiver/Server):
* Reads the message sent by Process 1 from the FIFO.
* Counts the number of characters, words, and lines in the message.
* Writes these counts into an `output.txt` file.
* Sends the counts back to Process 1 through a second FIFO.

---

## ⚙️ Concept Used — FIFO (Named Pipe)

A FIFO (First-In, First-Out), also known as a named pipe, is a special type of file that allows for data transfer between unrelated processes without requiring a common ancestor.

* They are created in the filesystem using the `mkfifo()` system call.
* One process can open the FIFO for writing, while another opens it for reading.
* They persist in the filesystem until explicitly removed (e.g., with `unlink()`).

In this project, two FIFOs facilitate bidirectional communication:
1.  `FIFO1` (`/tmp/fifo1`): Used by `process1` to send data **to** `process2`.
2.  `FIFO2` (`/tmp/fifo2`): Used by `process2` to send results back **to** `process1`.

---

## 🧾 File Descriptions

### 🟢 `process1.c`
**Role:** Acts as the sender/client. It reads input from the user and sends it to `process2` for processing.

**Key Steps:**
1.  Creates the two FIFOs, `/tmp/fifo1` and `/tmp/fifo2`, if they don't already exist.
2.  Prompts the user to enter sentences.
3.  Writes the user's input string into `FIFO1`.
4.  Blocks and waits to read the processed result from `process2` via `FIFO2`.
5.  Displays the output received from `process2`.
6.  The loop continues until the user types `exit`.
7.  Removes the FIFO files before terminating.

### 🔵 `process2.c`
**Role:** Acts as the receiver/server. It waits for data, processes it, and returns the results.

**Key Steps:**
1.  Creates the same two FIFOs, `/tmp/fifo1` and `/tmp/fifo2`.
2.  Enters a loop, continuously waiting to read data from `FIFO1`.
3.  Upon receiving data:
    * It counts the characters, words, and lines.
    * Stores the results in a local file named `output.txt`.
    * Writes the content of `output.txt` back to `process1` through `FIFO2`.
4.  If the received message is `"exit"`, it breaks the loop and terminates gracefully.
5.  Removes the FIFO files before exiting.

---

## 🧮 How Counting Works (`count_stats()` Function)
```c
void count_stats(const char *text, int *chars, int *words, int *lines)