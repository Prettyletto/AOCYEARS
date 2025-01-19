package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func returnInt(line string) []int {
	sides := strings.Fields(line)
	values := make([]int, len(sides))
	for i, v := range sides {
		var err error
		values[i], err = strconv.Atoi(v)
		if err != nil {
			fmt.Println("Error to convert line ")
			os.Exit(1)
		}
	}
	return values
}

func day1(line string) bool {
	values := returnInt(line)

	return isTriangle(values)
}

func isTriangle(values []int) bool {

	a, b, c := values[0], values[1], values[2]

	return a+b > c && b+c > a && a+c > b

}

func day2(lines []string) int {
	matrix := make([][]int, 3)
	triangle := make([]int, 3)
	sum := 0

	for i, v := range lines {
		matrix[i] = returnInt(v)
	}

	for i := 0; i < 3; i++ {

		for k := 0; k < 3; k++ {
			triangle[k] = matrix[k][i]
		}
		if isTriangle(triangle) {
			sum++
		}

	}
	return sum
}

func main() {

	if len(os.Args) != 2 {
		fmt.Println("Usage: <fileName>")
		return
	}

	source, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Printf("Could not open the file: %s\n", os.Args[1])
		return
	}
	defer source.Close()

	scanner := bufio.NewScanner(source)
	index := 0
	sum := 0
	var lines = make([]string, 3)

	for scanner.Scan() {

		line := scanner.Text()
		lines[index] = line

		index++
		if index > 2 {
			sum += day2(lines)
			index = 0
		}
	}
	fmt.Println(sum)
}
