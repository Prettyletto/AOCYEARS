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
	x      int
	y      int
	facing rune
}

func move(p *Point, direction rune, distance int) {
	switch p.facing {
	case 'N':
		if direction == 'R' {
			p.x += distance
			p.facing = 'E'
		} else {
			p.x -= distance
			p.facing = 'W'
		}
	case 'S':
		if direction == 'R' {
			p.x -= distance
			p.facing = 'W'
		} else {
			p.x += distance
			p.facing = 'E'
		}
	case 'E':
		if direction == 'R' {
			p.y -= distance
			p.facing = 'S'
		} else {
			p.y += distance
			p.facing = 'N'
		}
	case 'W':
		if direction == 'R' {
			p.y += distance
			p.facing = 'N'
		} else {
			p.y -= distance
			p.facing = 'S'
		}
	default:
	}
}

func moveUnit(p *Point, direction rune) {
	switch p.facing {
	case 'N':
		if direction == 'R' {
			p.x++
		} else {
			p.x--
		}
	case 'S':
		if direction == 'R' {
			p.x--
		} else {
			p.x++
		}
	case 'E':
		if direction == 'R' {
			p.y--
		} else {
			p.y++
		}
	case 'W':
		if direction == 'R' {
			p.y++
		} else {
			p.y--
		}
	default:
	}
}

func changeDirection(p *Point, direction rune) {
	switch p.facing {
	case 'N':
		if direction == 'R' {
			p.facing = 'E'
		} else {
			p.facing = 'W'
		}
	case 'S':
		if direction == 'R' {
			p.facing = 'W'
		} else {
			p.facing = 'E'
		}
	case 'E':
		if direction == 'R' {
			p.facing = 'S'
		} else {
			p.facing = 'N'
		}
	case 'W':
		if direction == 'R' {
			p.facing = 'N'
		} else {
			p.facing = 'S'
		}
	default:
	}
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
		point.facing = 'N'
		for i := 0; i < len(instructions); i++ {
			reading := strings.TrimSpace(instructions[i])
			letter := rune(reading[0])
			number, err := strconv.Atoi(reading[1:])
			if err != nil {
				log.Fatal(err)
			}
			for j := 0; j < number; j++ {
				moveUnit(&point, letter)
				tmpPoint := Point{x: point.x, y: point.y}
				if set[tmpPoint] {
					fmt.Println(math.Abs(float64(tmpPoint.x + tmpPoint.y)))

					return
				} else {
					set[tmpPoint] = true
				}
			}

			changeDirection(&point, letter)
		}

	}

}
