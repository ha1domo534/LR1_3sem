package main

import "fmt"

type DNode struct {
	data string
	prev *DNode
	next *DNode
}

type DList struct {
	head *DNode
	tail *DNode
}

func NewDList() *DList {
	return &DList{nil, nil}
}

func (list *DList) FindNode(value string) *DNode {
	for cur := list.head; cur != nil; cur = cur.next {
		if cur.data == value {
			return cur
		}
	}
	return nil
}

func (list *DList) PushFront(value string) {
	n := &DNode{value, nil, list.head}
	if list.head != nil {
		list.head.prev = n
	} else {
		list.tail = n
	}
	list.head = n
}

func (list *DList) PushBack(value string) {
	n := &DNode{value, list.tail, nil}
	if list.tail != nil {
		list.tail.next = n
	} else {
		list.head = n
	}
	list.tail = n
}

func (list *DList) PushAfter(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &DNode{value, p, p.next}
	if p.next != nil {
		p.next.prev = n
	} else {
		list.tail = n
	}
	p.next = n
	return true
}

func (list *DList) PushBefore(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &DNode{value, p.prev, p}
	if p.prev != nil {
		p.prev.next = n
	} else {
		list.head = n
	}
	p.prev = n
	return true
}

func (list *DList) unlink(node *DNode) {
	if node.prev != nil {
		node.prev.next = node.next
	} else {
		list.head = node.next
	}
	if node.next != nil {
		node.next.prev = node.prev
	} else {
		list.tail = node.prev
	}
}

func (list *DList) PopFront() (string, bool) {
	if list.head == nil {
		return "", false
	}
	value := list.head.data
	list.unlink(list.head)
	return value, true
}

func (list *DList) PopBack() (string, bool) {
	if list.tail == nil {
		return "", false
	}
	value := list.tail.data
	list.unlink(list.tail)
	return value, true
}

func (list *DList) RemoveAfter(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.next == nil {
		return "", false
	}
	value := p.next.data
	list.unlink(p.next)
	return value, true
}

func (list *DList) RemoveBefore(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.prev == nil {
		return "", false
	}
	value := p.prev.data
	list.unlink(p.prev)
	return value, true
}

func (list *DList) RemoveValue(value string) bool {
	p := list.FindNode(value)
	if p == nil {
		return false
	}
	list.unlink(p)
	return true
}

func (list *DList) GetAt(index int) (string, bool) {
	if index < 0 {
		return "", false
	}
	cur := list.head
	for i := 0; i < index && cur != nil; i++ {
		cur = cur.next
	}
	if cur == nil {
		return "", false
	}
	return cur.data, true
}

func (list *DList) Print() {
	if list.head == nil {
		fmt.Println("(empty)")
		return
	}
	for cur := list.head; cur != nil; cur = cur.next {
		fmt.Print(cur.data)
		if cur.next != nil {
			fmt.Print(" <-> ")
		}
	}
	fmt.Println()
}

func (list *DList) PrintReverse() {
	if list.tail == nil {
		fmt.Println("(empty)")
		return
	}
	for cur := list.tail; cur != nil; cur = cur.prev {
		fmt.Print(cur.data)
		if cur.prev != nil {
			fmt.Print(" <-> ")
		}
	}
	fmt.Println()
}
