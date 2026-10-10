package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// ============================================================
// 1. МАССИВ
// ============================================================
type Array struct {
	data []int
}

func (a *Array) PushBack(x int) { a.data = append(a.data, x) }

func (a *Array) PushAt(i, x int) {
	if i < 0 || i > len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return
	}
	a.data = append(a.data[:i], append([]int{x}, a.data[i:]...)...)
}

func (a *Array) Get(i int) int {
	if i < 0 || i >= len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return 0
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

func (a *Array) Set(i, x int) {
	if i < 0 || i >= len(a.data) {
		fmt.Println("-> ERROR: index out of range")
		return
	}
	a.data[i] = x
}

func (a *Array) Size() int { return len(a.data) }

func (a *Array) Print() {
	fmt.Print("[")
	for i, v := range a.data {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(v)
	}
	fmt.Println("]")
}

func (a *Array) All() []int     { return a.data }
func (a *Array) SetAll(v []int) { a.data = v }

// ============================================================
// 2. ОДНОСВЯЗНЫЙ СПИСОК
// ============================================================
type SNode struct {
	val  int
	next *SNode
}

type SinglyList struct {
	head *SNode
	cnt  int
}

func (l *SinglyList) PushFront(x int) {
	n := &SNode{val: x, next: l.head}
	l.head = n
	l.cnt++
}

func (l *SinglyList) PushBack(x int) {
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

func (l *SinglyList) PushAfter(target, x int) {
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

func (l *SinglyList) DelValue(x int) {
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

func (l *SinglyList) Find(x int) bool {
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
	fmt.Print("[")
	p := l.head
	first := true
	for p != nil {
		if !first {
			fmt.Print(", ")
		}
		fmt.Print(p.val)
		first = false
		p = p.next
	}
	fmt.Println("]")
}

func (l *SinglyList) All() []int {
	var v []int
	p := l.head
	for p != nil {
		v = append(v, p.val)
		p = p.next
	}
	return v
}

func (l *SinglyList) SetAll(v []int) {
	l.head = nil
	l.cnt = 0
	for _, x := range v {
		l.PushBack(x)
	}
}

// ============================================================
// 3. ДВУСВЯЗНЫЙ СПИСОК
// ============================================================
type DNode struct {
	val        int
	prev, next *DNode
}

type DoublyList struct {
	head, tail *DNode
	cnt        int
}

func (l *DoublyList) PushFront(x int) {
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

func (l *DoublyList) PushBack(x int) {
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

func (l *DoublyList) PushAfter(target, x int) {
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

func (l *DoublyList) DelValue(x int) {
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

func (l *DoublyList) Find(x int) bool {
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
	fmt.Print("[")
	p := l.head
	first := true
	for p != nil {
		if !first {
			fmt.Print(", ")
		}
		fmt.Print(p.val)
		first = false
		p = p.next
	}
	fmt.Println("]")
}

func (l *DoublyList) All() []int {
	var v []int
	p := l.head
	for p != nil {
		v = append(v, p.val)
		p = p.next
	}
	return v
}

func (l *DoublyList) SetAll(v []int) {
	l.head = nil
	l.tail = nil
	l.cnt = 0
	for _, x := range v {
		l.PushBack(x)
	}
}

// ============================================================
// 4. СТЕК
// ============================================================
type Stack struct {
	data []int
}

func (s *Stack) Push(x int) { s.data = append(s.data, x) }

func (s *Stack) Pop() {
	if len(s.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println("->", s.data[len(s.data)-1])
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
	fmt.Print("[")
	for i := len(s.data) - 1; i >= 0; i-- {
		fmt.Print(s.data[i])
		if i > 0 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}

func (s *Stack) All() []int     { return s.data }
func (s *Stack) SetAll(v []int) { s.data = v }

// ============================================================
// 5. ОЧЕРЕДЬ
// ============================================================
type Queue struct {
	data []int
}

func (q *Queue) Push(x int) { q.data = append(q.data, x) }

func (q *Queue) Pop() {
	if len(q.data) == 0 {
		fmt.Println("-> ERROR: empty")
		return
	}
	fmt.Println("->", q.data[0])
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
	fmt.Print("[")
	for i, v := range q.data {
		if i > 0 {
			fmt.Print(", ")
		}
		fmt.Print(v)
	}
	fmt.Println("]")
}

func (q *Queue) All() []int     { return q.data }
func (q *Queue) SetAll(v []int) { q.data = v }

// ============================================================
// ГЛОБАЛЬНЫЕ СЛОВАРИ
// ============================================================
var arrays = map[string]*Array{}
var flists = map[string]*SinglyList{}
var llists = map[string]*DoublyList{}
var stacks = map[string]*Stack{}
var queues = map[string]*Queue{}

// ============================================================
// ФАЙЛ: СОХРАНЕНИЕ / ЗАГРУЗКА
// ============================================================
func saveToFile(path string) {
	f, err := os.Create(path)
	if err != nil {
		fmt.Println("-> ERROR: cannot write file")
		return
	}
	defer f.Close()
	w := bufio.NewWriter(f)
	defer w.Flush()

	writeLine := func(prefix, name string, vals []int) {
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
		var vals []int
		for _, tok := range parts[2:] {
			x, err := strconv.Atoi(tok)
			if err == nil {
				vals = append(vals, x)
			}
		}
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

// ============================================================
// ВСПОМОГАТЕЛЬНОЕ
// ============================================================
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

// ============================================================
// ОБРАБОТКА КОМАНД
// ============================================================
func processCommand(query string) {
	parts := strings.Fields(query)
	if len(parts) < 2 {
		fmt.Println("-> ERROR: empty command")
		return
	}
	cmd := parts[0]
	name := parts[1]
	rest := parts[2:]

	switch cmd {
	// ---------- МАССИВ ----------
	case "MPUSH":
		if len(rest) == 1 {
			getArray(name).PushBack(atoi(rest[0]))
			fmt.Println("-> OK")
		} else if len(rest) == 2 {
			getArray(name).PushAt(atoi(rest[0]), atoi(rest[1]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: MPUSH <name> <value> | <name> <idx> <value>")
		}
		return
	case "MGET":
		if len(rest) == 1 {
			fmt.Println("->", getArray(name).Get(atoi(rest[0])))
		} else {
			fmt.Println("-> ERROR: MGET <name> <idx>")
		}
		return
	case "MDEL":
		if len(rest) == 1 {
			getArray(name).Del(atoi(rest[0]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: MDEL <name> <idx>")
		}
		return
	case "MSET":
		if len(rest) == 2 {
			getArray(name).Set(atoi(rest[0]), atoi(rest[1]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: MSET <name> <idx> <value>")
		}
		return
	case "MSIZE":
		fmt.Println("->", getArray(name).Size())
		return

	// ---------- ОДНОСВЯЗНЫЙ СПИСОК ----------
	case "FPUSH":
		if len(rest) == 1 {
			getFList(name).PushBack(atoi(rest[0]))
			fmt.Println("-> OK")
		} else if len(rest) == 2 {
			where := rest[0]
			v := atoi(rest[1])
			if where == "front" || where == "head" {
				getFList(name).PushFront(v)
			} else if where == "back" || where == "tail" {
				getFList(name).PushBack(v)
			} else {
				getFList(name).PushAfter(atoi(where), v)
			}
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: FPUSH <name> <value> | <name> front|back|target <value>")
		}
		return
	case "FDEL":
		if len(rest) == 1 {
			what := rest[0]
			if what == "front" || what == "head" {
				getFList(name).DelFront()
			} else if what == "back" || what == "tail" {
				getFList(name).DelBack()
			} else {
				getFList(name).DelValue(atoi(what))
			}
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: FDEL <name> front|back|value")
		}
		return
	case "FGET":
		if len(rest) == 1 {
			if getFList(name).Find(atoi(rest[0])) {
				fmt.Println("-> TRUE")
			} else {
				fmt.Println("-> FALSE")
			}
		} else {
			fmt.Println("-> ERROR: FGET <name> <value>")
		}
		return
	case "FSIZE":
		fmt.Println("->", getFList(name).Size())
		return

	// ---------- ДВУСВЯЗНЫЙ СПИСОК ----------
	case "LPUSH":
		if len(rest) == 1 {
			getLList(name).PushBack(atoi(rest[0]))
			fmt.Println("-> OK")
		} else if len(rest) == 2 {
			where := rest[0]
			v := atoi(rest[1])
			if where == "front" || where == "head" {
				getLList(name).PushFront(v)
			} else if where == "back" || where == "tail" {
				getLList(name).PushBack(v)
			} else {
				getLList(name).PushAfter(atoi(where), v)
			}
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: LPUSH <name> <value> | <name> front|back|target <value>")
		}
		return
	case "LDEL":
		if len(rest) == 1 {
			what := rest[0]
			if what == "front" || what == "head" {
				getLList(name).DelFront()
			} else if what == "back" || what == "tail" {
				getLList(name).DelBack()
			} else {
				getLList(name).DelValue(atoi(what))
			}
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: LDEL <name> front|back|value")
		}
		return
	case "LGET":
		if len(rest) == 1 {
			if getLList(name).Find(atoi(rest[0])) {
				fmt.Println("-> TRUE")
			} else {
				fmt.Println("-> FALSE")
			}
		} else {
			fmt.Println("-> ERROR: LGET <name> <value>")
		}
		return
	case "LSIZE":
		fmt.Println("->", getLList(name).Size())
		return

	// ---------- СТЕК ----------
	case "SPUSH":
		if len(rest) == 1 {
			getStack(name).Push(atoi(rest[0]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: SPUSH <name> <value>")
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

	// ---------- ОЧЕРЕДЬ ----------
	case "QPUSH":
		if len(rest) == 1 {
			getQueue(name).Push(atoi(rest[0]))
			fmt.Println("-> OK")
		} else {
			fmt.Println("-> ERROR: QPUSH <name> <value>")
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

	// ---------- PRINT ----------
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

// ============================================================
// MAIN
// ============================================================
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
		fmt.Println("Usage: ./dbms --file <file> --query '<command>'")
		return
	}

	loadFromFile(filePath)
	processCommand(query)
	saveToFile(filePath)
}
