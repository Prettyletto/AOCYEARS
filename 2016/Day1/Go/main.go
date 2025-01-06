package main

import (
	"bufio"
	"fmt"
	"log"
	"math"
	"os"
	"strconv"
	"strings"
)

type Point struct {
	x int
	y int
}

var DIR = [4]Point{
	{0, 1}, {1, 0}, {0, -1}, {-1, 0},
}

func (p Point) String() string {
	return fmt.Sprintf("Point {x:%d y:%d}", p.x, p.y)
}

func main() {
	if len(os.Args) != 2 {
		fmt.Printf("Usage of %s: [file path]", os.Args[0])
		return
	}

	source, err := os.Open(os.Args[1])
	if err != nil {
		log.Fatal(err)
	}
	defer source.Close()

	scanner := bufio.NewScanner(source)

	for scanner.Scan() {
		line := scanner.Text()
		instructions := strings.Split(line, ",")
		set := make(map[Point]bool)
		var point Point
		facing := 0

		for i := range instructions {
			reading := strings.TrimSpace(instructions[i])
			ins := rune(reading[0])
			number, err := strconv.Atoi(reading[1:])
			if err != nil {
				log.Fatal(err)
			}
			turn := 1
			if ins == 'L' {
				turn = -1
			}
			facing = (facing + turn + len(DIR)) % len(DIR)
			for j := 0; j < number; j++ {
				point.x += DIR[facing].x
				point.y += DIR[facing].y

				if set[point] {
					fmt.Println(math.Abs(float64(point.x + point.y)))
					return
				} else {
					set[point] = true
				}
			}

		}

	}

}
