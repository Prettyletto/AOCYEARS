package main

import (
	"crypto/md5"
	"encoding/hex"
	"fmt"
)

const (
	KEY = "cxdnnyjw"
)

func GetHash(text string) string {
	hash := md5.Sum([]byte(text))
	return hex.EncodeToString(hash[:])
}

func main() {

	var index uint64 = 0
	i := 0
	passw := []byte{'*', '*', '*', '*', '*', '*', '*', '*'}

	for i < 8 {
		finding := fmt.Sprintf("%s%d", KEY, index)
		hashed := GetHash(finding)
		sub := hashed[:5]
		pos := hashed[5] - '0'
		if sub == "00000" {
			if pos >= 0 && pos <= 7 {
				if passw[pos] == '*' {
					passw[pos] = hashed[6]
					i++
				}
			}
		}
		index++
	}
	fmt.Println(string(passw))

}
