<h1 align="center">minitalk</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C"/>
</p>

<p align="center"><strong>A client and a server that exchange a string using nothing but Unix signals, one bit at a time.</strong></p>

---

## 📌 Overview

Unix signals predate sockets and pipes: `kill()` and a handler are the whole interface, and the payload is a signal number, nothing more.
minitalk turns that into a wire protocol by using two signals, `SIGUSR1` and `SIGUSR2`, as the only two symbols an alphabet needs, 0 and 1.
The client shifts a string out bit by bit as a stream of signals; the server rebuilds it one bit at a time in a handler that runs asynchronously, with no return value and no argument beyond the signal itself.
Getting this right means designing a protocol on top of a channel that carries a single bit of information per delivery, and doing it inside the tight constraints of signal-safe code.

## 🎯 Objectives

- Transmit an arbitrary string from a client process to a server process using only `kill()` and `sigaction()`, no sockets, pipes or shared memory
- Encode each byte of the message as eight signal deliveries, `SIGUSR1` for 0 and `SIGUSR2` for 1
- Acknowledge each bit back to the sender so the client knows the server actually received it, rather than firing signals blind
- Handle more than one client without corrupting either message: a second client mid-conversation is told the server is busy instead of interleaving with the first
- Recover from an unreachable PID, a malformed argument list or a signal from an unexpected sender without hanging or crashing

## 🛠️ Tech Stack

<p>
  <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C"/>
</p>

## 🚀 Getting Started

```bash
git clone https://github.com/acardona123/42_minitalk.git
cd 42_minitalk/srcs
make
```

## 📖 Usage

```bash
./server
# PID : 12345

./client 12345 "hello"
```

The server prints its PID on startup; the client needs that PID as its first argument and the message as its second.
Any other argument count, or a PID that is not a positive number, is rejected before a single signal is sent.

## 🧪 Tests

No automated suite ships in this repo; correctness was checked by hand against strings that stress the bit-packing rather than just the happy path: `arabe.txt` at the root is a right-to-left, multi-byte UTF-8 string, and `srcs/joli.txt` / `srcs/test.txt` push longer payloads through the same client.
Validated against [42_tester_minitalk](https://github.com/acardona123/42_tester_minitalk), which runs the throughput and multibyte cases as a repeatable script.

## 📁 Structure

```
srcs/
├── client.c        client: encodes the message, waits for each ACK, reports server errors
├── server.c        server: rebuilds the message bit by bit, tracks the current sender's PID
├── ft_atoi.c        argument parsing
├── ft_putnbr_fd.c   PID output
├── minitalk.h
└── Makefile
```

## 📚 Resources

- [Shichao's Notes, chapter 10: Signals](https://notes.shichao.io/apue/ch10/), the APUE chapter this project was built against

---

<p align="center"><sub>🏫 Project from the <strong>42</strong> common core, School 42 Paris.</sub></p>
