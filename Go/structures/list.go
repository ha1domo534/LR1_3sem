package main

import "fmt"

type FNode struct {
	data string
	next *FNode
}

type FList struct {
	head *FNode
	tail *FNode
}

func NewFList() *FList {
	return &FList{nil, nil}
}

func (list *FList) FindNode(value string) *FNode {
	cur := list.head
	for cur != nil {
		if cur.data == value {
			return cur
		}
		cur = cur.next
	}
	return nil
}

func (list *FList) PushFront(value string) {
	n := &FNode{value, list.head}
	list.head = n
	if list.tail == nil {
		list.tail = n
	}
}

func (list *FList) PushBack(value string) {
	n := &FNode{value, nil}
	if list.tail == nil {
		list.head = n
		list.tail = n
	} else {
		list.tail.next = n
		list.tail = n
	}
}

func (list *FList) PushAfter(target, value string) bool {
	p := list.FindNode(target)
	if p == nil {
		return false
	}
	n := &FNode{value, p.next}
	p.next = n
	if p == list.tail {
		list.tail = n
	}
	return true
}

func (list *FList) PushBefore(target, value string) bool {
	if list.head == nil {
		return false
	}
	if list.head.data == target {
		list.PushFront(value)
		return true
	}
	prev := list.head
	for prev.next != nil && prev.next.data != target {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	prev.next = &FNode{value, prev.next}
	return true
}

func (list *FList) PopFront() (string, bool) {
	if list.head == nil {
		return "", false
	}
	old := list.head
	list.head = old.next
	if list.head == nil {
		list.tail = nil
	}
	return old.data, true
}

func (list *FList) PopBack() (string, bool) {
	if list.head == nil {
		return "", false
	}
	if list.head == list.tail {
		value := list.head.data
		list.head = nil
		list.tail = nil
		return value, true
	}
	prev := list.head
	for prev.next != list.tail {
		prev = prev.next
	}
	value := list.tail.data
	list.tail = prev
	list.tail.next = nil
	return value, true
}

func (list *FList) RemoveAfter(target string) (string, bool) {
	p := list.FindNode(target)
	if p == nil || p.next == nil {
		return "", false
	}
	victim := p.next
	p.next = victim.next
	if victim == list.tail {
		list.tail = p
	}
	return victim.data, true
}

func (list *FList) RemoveBefore(target string) (string, bool) {
	if list.head == nil || list.head.data == target || list.head.next == nil {
		return "", false
	}
	if list.head.next.data == target {
		return list.PopFront()
	}
	prev := list.head
	for prev.next.next != nil && prev.next.next.data != target {
		prev = prev.next
	}
	if prev.next.next == nil {
		return "", false
	}
	victim := prev.next
	prev.next = victim.next
	return victim.data, true
}

func (list *FList) RemoveValue(value string) bool {
	if list.head == nil {
		return false
	}
	if list.head.data == value {
		list.PopFront()
		return true
	}
	prev := list.head
	for prev.next != nil && prev.next.data != value {
		prev = prev.next
	}
	if prev.next == nil {
		return false
	}
	victim := prev.next
	prev.next = victim.next
	if victim == list.tail {
		list.tail = prev
	}
	return true
}

func (list *FList) GetAt(index int) (string, bool) {
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

func (list *FList) Print() {
	if list.head == nil {
		fmt.Println("(empty)")
		return
	}
	for cur := list.head; cur != nil; cur = cur.next {
		fmt.Print(cur.data)
		if cur.next != nil {
			fmt.Print(" -> ")
		}
	}
	fmt.Println()
}

func printReverseRec(node *FNode) {
	if node == nil {
		return
	}
	printReverseRec(node.next)
	fmt.Print(node.data, " ")
}

func (list *FList) PrintReverse() {
	if list.head == nil {
		fmt.Println("(empty)")
		return
	}
	printReverseRec(list.head)
	fmt.Println()
}
