package main

import (
	"bufio"
	"fmt"
	"os"
)

type Point struct {
	y int
	x int
}

func day1(point *Point, move Point) {
	point.x += move.x
	if point.x < 0 {
		point.x = 0
	}
	if point.x > 2 {
		point.x = 2
	}
	point.y += move.y
	if point.y < 0 {
		point.y = 0
	}
	if point.y > 2 {
		point.y = 2
	}
}

func day2(point *Point, move Point, matrix [5][5]string) {
	tmp := point.x
	point.x += move.x
	if point.x > 4 || point.x < 0 || matrix[point.y][point.x] == "" {
		point.x = tmp
		return
	}
	tmp1 := point.y
	point.y += move.y
	if point.y > 4 || point.y < 0 || matrix[point.y][point.x] == "" {
		point.y = tmp1
		return
	}
}

var DIR = map[rune]Point{'L': {0, -1}, 'R': {0, 1}, 'U': {-1, 0}, 'D': {1, 0}}

var matrix2 = [5][5]string{
	{"", "", "1", "", ""},
	{"", "2", "3", "4", ""},
	{"5", "6", "7", "8", "9"},
	{"", "A", "B", "C", ""},
	{"", "", "D", "", ""},
}

var matrix = [3][3]int{
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: <file> ")
		return
	}

	source, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Println(err)
		return
	}
	defer source.Close()

	scanner := bufio.NewScanner(source)
	start := Point{2, 0}

	for scanner.Scan() {
		line := scanner.Text()

		for _, v := range line {
			day2(&start, DIR[v], matrix2)
		}
		fmt.Println(matrix2[start.y][start.x])
	}

}
