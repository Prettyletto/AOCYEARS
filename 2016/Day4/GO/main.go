package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Pair struct {
	letter byte
	count  int
}

type PairList []Pair

func (p Pair) String() string {
	return fmt.Sprintf("letter: %c, count:%d", p.letter, p.count)
}

func (p PairList) Len() int {
	return len(p)
}

func (p PairList) Less(i, j int) bool {
	if p[i].count == p[j].count {
		return p[i].letter < p[j].letter
	}

	return p[i].count > p[j].count
}

func (p PairList) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]

}

func rankLetters(letters map[byte]int) PairList {
	pl := make(PairList, 0, len(letters))
	for k, v := range letters {
		pl = append(pl, Pair{k, v})
	}
	sort.Sort(pl)

	return pl
}

func day1(line string) int {
	letters := make(map[byte]int, 0)
	splitted := strings.Split(line, "-")
	values := splitted[:len(splitted)-1]
	checkSum := strings.Split(splitted[len(splitted)-1:][0], "[")
	id, err := strconv.Atoi(checkSum[0])
	if err != nil {
		log.Fatal("Error trying to convert the number")
	}
	check := strings.Trim(checkSum[1], "]")

	for _, v := range values {
		for i := range v {
			_, ok := letters[v[i]]
			if ok {
				letters[v[i]]++
				continue
			}
			letters[v[i]] = 1
		}
	}
	pl := rankLetters(letters)

	for i := range check {
		if pl[i].letter != byte(check[i]) {
			return 0
		}
	}

	return id
}

func day2(line string) {
	splitted := strings.Split(line, "-")
	checkSum := strings.Split(splitted[len(splitted)-1:][0], "[")
	id, err := strconv.Atoi(checkSum[0])
	if err != nil {
		log.Fatal("Error trying to convert the number")
	}

	sb := strings.Builder{}
	for i := range line {

		c := rune(line[i])
		if c >= '0' && c <= '9' {
			break
		}
		if c == '-' {
			c = ' '
			sb.WriteRune(c)
			continue
		}
		write := rune((c-'a'+rune(id))%26 + 'a')

		if _, err := sb.WriteRune(write); err != nil {
			fmt.Println(err)
		}
	}
	fmt.Println(sb.String(), id)
}

func main() {
	if len(os.Args) != 2 {
		fmt.Printf("%s usage: fileName\n", os.Args[0])
		return
	}

	source, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Println("Error trying to open file ")
		return
	}

	scanner := bufio.NewScanner(source)
	sum := 0

	for scanner.Scan() {
		line := scanner.Text()
		day2(line)
	}

	fmt.Println(sum)
}
