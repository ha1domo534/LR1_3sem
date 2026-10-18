package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// 1. Array

type Array struct {
	data []string
}

func (a *Array) PushBack(x string) { a.data = append(a.data, x) }

func (a *Array) PushAt(i int, x string) {
	if i < 0 || i > len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return
	}
	a.data = append(a.data[:i], append([]string{x}, a.data[i:]...)...)
}

func (a *Array) Get(i int) string {
	if i < 0 || i >= len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return ""
	}
	return a.data[i]
}

func (a *Array) Del(i int) {
	if i < 0 || i >= len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return
	}
	a.data = append(a.data[:i], a.data[i+1:]...)
}

func (a *Array) Set(i int, x string) {
	if i < 0 || i >= len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return
	}
	a.data[i] = x
}

func (a *Array) Size() int { return len(a.data) }

func (a *Array) Print() {
	for i, v := range a.data {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(v)
	}
	fmt.Println()
}

func (a *Array) All() []string     { return a.data }
func (a *Array) SetAll(v []string) { a.data = v }

// 2. SinglyList

type SNode struct {
	val  string
	next *SNode
}

type SinglyList struct {
	head *SNode
	cnt  int
}

func (l *SinglyList) PushFront(x string) {
	n := &SNode{val: x, next: l.head}
	l.head = n
	l.cnt++
}

func (l *SinglyList) PushBack(x string) {
	n := &SNode{val: x}
	if l.head == nil {
		l.head = n
	} else {
		p := l.head
		for p.next != nil {
			p = p.next
		}
		p.next = n
	}
	l.cnt++
}

func (l *SinglyList) PushBefore(target, x string) {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	if l.head.val == target {
		l.PushFront(x)
		return
	}
	p := l.head
	for p.next != nil && p.next.val != target {
		p = p.next
	}
	if p.next == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	n := &SNode{val: x, next: p.next}
	p.next = n
	l.cnt++
}

func (l *SinglyList) PushAfter(target, x string) {
	p := l.head
	for p != nil && p.val != target {
		p = p.next
	}
	if p == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	n := &SNode{val: x, next: p.next}
	p.next = n
	l.cnt++
}

func (l *SinglyList) DelFront() {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	l.head = l.head.next
	l.cnt--
}

func (l *SinglyList) DelBack() {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	if l.head.next == nil {
		l.head = nil
		l.cnt--
		return
	}
	p := l.head
	for p.next.next != nil {
		p = p.next
	}
	p.next = nil
	l.cnt--
}

func (l *SinglyList) DelValue(x string) {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	if l.head.val == x {
		l.DelFront()
		return
	}
	p := l.head
	for p.next != nil && p.next.val != x {
		p = p.next
	}
	if p.next == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	p.next = p.next.next
	l.cnt--
}

func (l *SinglyList) Find(x string) bool {
	p := l.head
	for p != nil {
		if p.val == x {
			return true
		}
		p = p.next
	}
	return false
}

func (l *SinglyList) Size() int { return l.cnt }

func (l *SinglyList) Print() {
	p := l.head
	for p != nil {
		fmt.Print(p.val, " ")
		p = p.next
	}
	fmt.Println()
}

func (l *SinglyList) All() []string {
	var v []string
	p := l.head
	for p != nil {
		v = append(v, p.val)
		p = p.next
	}
	return v
}

func (l *SinglyList) SetAll(v []string) {
	l.head = nil
	l.cnt = 0
	for _, x := range v {
		l.PushBack(x)
	}
}

// 3. DoublyList

type DNode struct {
	val        string
	prev, next *DNode
}

type DoublyList struct {
	head, tail *DNode
	cnt        int
}

func (l *DoublyList) PushFront(x string) {
	n := &DNode{val: x, next: l.head}
	if l.head != nil {
		l.head.prev = n
	}
	l.head = n
	if l.tail == nil {
		l.tail = n
	}
	l.cnt++
}

func (l *DoublyList) PushBack(x string) {
	n := &DNode{val: x, prev: l.tail}
	if l.tail != nil {
		l.tail.next = n
	}
	l.tail = n
	if l.head == nil {
		l.head = n
	}
	l.cnt++
}

func (l *DoublyList) PushBefore(target, x string) {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	if l.head.val == target {
		l.PushFront(x)
		return
	}
	p := l.head
	for p != nil && p.val != target {
		p = p.next
	}
	if p == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	n := &DNode{val: x, prev: p.prev, next: p}
	p.prev.next = n
	p.prev = n
	l.cnt++
}

func (l *DoublyList) PushAfter(target, x string) {
	p := l.head
	for p != nil && p.val != target {
		p = p.next
	}
	if p == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	n := &DNode{val: x, prev: p, next: p.next}
	if p.next != nil {
		p.next.prev = n
	}
	p.next = n
	if l.tail == p {
		l.tail = n
	}
	l.cnt++
}

func (l *DoublyList) DelFront() {
	if l.head == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	l.cnt--
}

func (l *DoublyList) DelBack() {
	if l.tail == nil {
		fmt.Println("-> ERROR: empty")
		return
	}
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	l.cnt--
}

func (l *DoublyList) DelValue(x string) {
	p := l.head
	for p != nil && p.val != x {
		p = p.next
	}
	if p == nil {
		fmt.Println("-> ERROR: not found")
		return
	}
	if p == l.head {
		l.DelFront()
		return
	}
	if p == l.tail {
		l.DelBack()
		return
	}
	p.prev.next = p.next
	p.next.prev = p.prev
	l.cnt--
}

func (l *DoublyList) Find(x string) bool {
	p := l.head
	for p != nil {
		if p.val == x {
			return true
		}
		p = p.next
	}
	return false
}

func (l *DoublyList) Size() int { return l.cnt }

func (l *DoublyList) Print() {
	p := l.head
	first := true
	for p != nil {
		if !first {
			fmt.Print(" <-> ")
		}
		fmt.Print(p.val)
		first = false
		p = p.next
	}
	fmt.Println()
}

func (l *DoublyList) All() []string {
	var v []string
	p := l.head
	for p != nil {
		v = append(v, p.val)
		p = p.next
	}
	return v
}

func (l *DoublyList) SetAll(v []string) {
	l.head = nil
	l.tail = nil
	l.cnt = 0
	for _, x := range v {
		l.PushBack(x)
	}
}

// 4. Stack

type Stack struct {
	data []string
}

func (s *Stack) Push(x string) { s.data = append(s.data, x) }

func (s *Stack) Pop() {
	if len(s.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println(s.data[len(s.data)-1])
	s.data = s.data[:len(s.data)-1]
}

func (s *Stack) Peek() {
	if len(s.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println("->", s.data[len(s.data)-1])
}

func (s *Stack) Size() int { return len(s.data) }

func (s *Stack) Print() {
	for i := len(s.data) - 1; i >= 0; i-- {
		fmt.Println(s.data[i])
	}
}

func (s *Stack) All() []string     { return s.data }
func (s *Stack) SetAll(v []string) { s.data = v }

// 5. Queue

type Queue struct {
	data []string
}

func (q *Queue) Push(x string) { q.data = append(q.data, x) }

func (q *Queue) Pop() {
	if len(q.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println(q.data[0])
	q.data = q.data[1:]
}

func (q *Queue) Peek() {
	if len(q.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println("->", q.data[0])
}

func (q *Queue) Size() int { return len(q.data) }

func (q *Queue) Print() {
	for i, v := range q.data {
		if i > 0 {
			fmt.Print(" ")
		}
		fmt.Print(v)
	}
	fmt.Println()
}

func (q *Queue) All() []string     { return q.data }
func (q *Queue) SetAll(v []string) { q.data = v }

// словари

var arrays = map[string]*Array{}
var flists = map[string]*SinglyList{}
var llists = map[string]*DoublyList{}
var stacks = map[string]*Stack{}
var queues = map[string]*Queue{}

// Файл: сохранение / загрузка

func saveToFile(path string) {
	f, err := os.Create(path)
	if err != nil {
		return
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	defer w.Flush()

	writeLine := func(prefix, name string, vals []string) {
		fmt.Fprint(w, prefix, " ", name)
		for _, x := range vals {
			fmt.Fprint(w, " ", x)
		}
		fmt.Fprintln(w)
	}

	for n, s := range arrays {
		writeLine("ARRAY", n, s.All())
	}
	for n, s := range flists {
		writeLine("FLIST", n, s.All())
	}
	for n, s := range llists {
		writeLine("LLIST", n, s.All())
	}
	for n, s := range stacks {
		writeLine("STACK", n, s.All())
	}
	for n, s := range queues {
		writeLine("QUEUE", n, s.All())
	}
}

func loadFromFile(path string) {
	f, err := os.Open(path)
	if err != nil {
		return
	}
	defer f.Close()

	sc := bufio.NewScanner(f)
	for sc.Scan() {
		line := sc.Text()
		parts := strings.Fields(line)
		if len(parts) < 2 {
			continue
		}
		typ, name := parts[0], parts[1]
		vals := parts[2:]

		switch typ {
		case "ARRAY":
			arrays[name] = &Array{}
			arrays[name].SetAll(vals)
		case "FLIST":
			flists[name] = &SinglyList{}
			flists[name].SetAll(vals)
		case "LLIST":
			llists[name] = &DoublyList{}
			llists[name].SetAll(vals)
		case "STACK":
			stacks[name] = &Stack{}
			stacks[name].SetAll(vals)
		case "QUEUE":
			queues[name] = &Queue{}
			queues[name].SetAll(vals)
		}
	}
}

// ВСПОМОГАТЕЛЬНОЕ

func atoi(s string) int {
	x, _ := strconv.Atoi(s)
	return x
}

func getArray(name string) *Array {
	if _, ok := arrays[name]; !ok {
		arrays[name] = &Array{}
	}
	return arrays[name]
}
func getFList(name string) *SinglyList {
	if _, ok := flists[name]; !ok {
		flists[name] = &SinglyList{}
	}
	return flists[name]
}
func getLList(name string) *DoublyList {
	if _, ok := llists[name]; !ok {
		llists[name] = &DoublyList{}
	}
	return llists[name]
}
func getStack(name string) *Stack {
	if _, ok := stacks[name]; !ok {
		stacks[name] = &Stack{}
	}
	return stacks[name]
}
func getQueue(name string) *Queue {
	if _, ok := queues[name]; !ok {
		queues[name] = &Queue{}
	}
	return queues[name]
}

// Обработка команд

func processCommand(query string) {
	parts := strings.Fields(query)
	if len(parts) < 2 {
		fmt.Println("-> ERROR: empty command")
		return
	}
	cmd := parts[0]
	name := parts[1]
	rest := parts[2:]

	// Create
	switch cmd {
	case "MCREATE":
		if _, ok := arrays[name]; ok {
			fmt.Println("-> ERROR: array exists")
			return
		}
		arrays[name] = &Array{}
		fmt.Println("-> OK")
		return
	case "FCREATE":
		if _, ok := flists[name]; ok {
			fmt.Println("-> ERROR: list exists")
			return
		}
		flists[name] = &SinglyList{}
		fmt.Println("-> OK")
		return
	case "LCREATE":
		if _, ok := llists[name]; ok {
			fmt.Println("-> ERROR: list exists")
			return
		}
		llists[name] = &DoublyList{}
		fmt.Println("-> OK")
		return
	case "SCREATE":
		if _, ok := stacks[name]; ok {
			fmt.Println("-> ERROR: stack exists")
			return
		}
		stacks[name] = &Stack{}
		fmt.Println("-> OK")
		return
	case "QCREATE":
		if _, ok := queues[name]; ok {
			fmt.Println("-> ERROR: queue exists")
			return
		}
		queues[name] = &Queue{}
		fmt.Println("-> OK")
		return
	}

	// array
	switch cmd {
	case "MPUSH":
		if len(rest) == 1 {
			getArray(name).PushBack(rest[0])
			fmt.Println("->", rest[0])
		} else if len(rest) == 2 {
			getArray(name).PushAt(atoi(rest[0]), rest[1])
			fmt.Println("->", rest[1])
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "MGET":
		if len(rest) == 1 {
			fmt.Println("->", getArray(name).Get(atoi(rest[0])))
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "MDEL":
		if len(rest) == 1 {
			getArray(name).Del(atoi(rest[0]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "MSET":
		if len(rest) == 2 {
			getArray(name).Set(atoi(rest[0]), rest[1])
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "MSIZE":
		fmt.Println("->", getArray(name).Size())
		return

	// list
	case "FPUSHHEAD":
		if len(rest) == 1 {
			getFList(name).PushFront(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для FPUSHHEAD")
		}
		return
	case "FPUSHTAIL":
		if len(rest) == 1 {
			getFList(name).PushBack(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для FPUSHTAIL")
		}
		return
	case "FPUSHBEFORE":
		if len(rest) == 2 {
			getFList(name).PushBefore(rest[0], rest[1])
			fmt.Println("->", rest[1])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для FPUSHBEFORE")
		}
		return
	case "FPUSHAFTER":
		if len(rest) == 2 {
			getFList(name).PushAfter(rest[0], rest[1])
			fmt.Println("->", rest[1])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для FPUSHAFTER")
		}
		return
	case "FDELHEAD":
		getFList(name).DelFront()
		fmt.Println("-> OK")
		return
	case "FDELTAIL":
		getFList(name).DelBack()
		fmt.Println("-> OK")
		return
	case "FDELVAL":
		if len(rest) == 1 {
			getFList(name).DelValue(rest[0])
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "FGET":
		if len(rest) == 1 {
			if getFList(name).Find(rest[0]) {
				fmt.Println("-> TRUE")
			} else {
				fmt.Println("-> FALSE")
			}
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "FSIZE":
		fmt.Println("->", getFList(name).Size())
		return

	// double list
	case "LPUSHHEAD":
		if len(rest) == 1 {
			getLList(name).PushFront(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для LPUSHHEAD")
		}
		return
	case "LPUSHTAIL":
		if len(rest) == 1 {
			getLList(name).PushBack(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для LPUSHTAIL")
		}
		return
	case "LPUSHBEFORE":
		if len(rest) == 2 {
			getLList(name).PushBefore(rest[0], rest[1])
			fmt.Println("->", rest[1])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для LPUSHBEFORE")
		}
		return
	case "LPUSHAFTER":
		if len(rest) == 2 {
			getLList(name).PushAfter(rest[0], rest[1])
			fmt.Println("->", rest[1])
		} else {
			fmt.Println("-> Ошибка: неверное количество аргументов для LPUSHAFTER")
		}
		return
	case "LDELHEAD":
		getLList(name).DelFront()
		fmt.Println("-> OK")
		return
	case "LDELTAIL":
		getLList(name).DelBack()
		fmt.Println("-> OK")
		return
	case "LDELVAL":
		if len(rest) == 1 {
			getLList(name).DelValue(rest[0])
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "LGET":
		if len(rest) == 1 {
			if getLList(name).Find(rest[0]) {
				fmt.Println("-> TRUE")
			} else {
				fmt.Println("-> FALSE")
			}
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "LSIZE":
		fmt.Println("->", getLList(name).Size())
		return

	//Stack
	case "SPUSH":
		if len(rest) == 1 {
			getStack(name).Push(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "SPOP":
		getStack(name).Pop()
		return
	case "SPEEK":
		getStack(name).Peek()
		return
	case "SSIZE":
		fmt.Println("->", getStack(name).Size())
		return

	// Queue
	case "QPUSH":
		if len(rest) == 1 {
			getQueue(name).Push(rest[0])
			fmt.Println("->", rest[0])
		} else {
			fmt.Println("-> ERROR: format")
		}
		return
	case "QPOP":
		getQueue(name).Pop()
		return
	case "QPEEK":
		getQueue(name).Peek()
		return
	case "QSIZE":
		fmt.Println("->", getQueue(name).Size())
		return

	//Print
	case "PRINT":
		if s, ok := arrays[name]; ok {
			s.Print()
			return
		}
		if s, ok := flists[name]; ok {
			s.Print()
			return
		}
		if s, ok := llists[name]; ok {
			s.Print()
			return
		}
		if s, ok := stacks[name]; ok {
			s.Print()
			return
		}
		if s, ok := queues[name]; ok {
			s.Print()
			return
		}
		fmt.Println("-> ERROR: '" + name + "' not found")
		return
	}

	fmt.Println("-> ERROR: unknown command '" + cmd + "'")
}

// Main
func main() {
	var filePath, query string
	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "--file":
			if i+1 < len(args) {
				filePath = args[i+1]
				i++
			}
		case "--query":
			if i+1 < len(args) {
				query = args[i+1]
				i++
			}
		}
	}

	if filePath == "" || query == "" {
		fmt.Println("Usage: ./LR1_go --file <file> --query '<command>'")
		return
	}

	loadFromFile(filePath)
	processCommand(query)
	saveToFile(filePath)
}
