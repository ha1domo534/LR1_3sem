package main

import (
	"fmt"
	"strings"
)

type Array struct {
	data []string
}

func NewArray() *Array {
	return &Array{data: make([]string, 0)}
}

func (arr *Array) PushBack(value string) {
	arr.data = append(arr.data, value)
}

func (arr *Array) InsertAt(index int, value string) bool {
	if index < 0 || index > len(arr.data) {
		return false
	}
	arr.data = append(arr.data[:index], append([]string{value}, arr.data[index:]...)...)
	return true
}

func (arr *Array) GetAt(index int) (string, bool) {
	if index < 0 || index >= len(arr.data) {
		return "", false
	}
	return arr.data[index], true
}

func (arr *Array) SetAt(index int, value string) bool {
	if index < 0 || index >= len(arr.data) {
		return false
	}
	arr.data[index] = value
	return true
}

func (arr *Array) RemoveAt(index int) bool {
	if index < 0 || index >= len(arr.data) {
		return false
	}
	arr.data = append(arr.data[:index], arr.data[index+1:]...)
	return true
}

func (arr *Array) Length() int {
	return len(arr.data)
}

func (arr *Array) String() string {
	return "[" + strings.Join(arr.data, ", ") + "]"
}

func (arr *Array) Print() {
	fmt.Println(arr.String())
}
