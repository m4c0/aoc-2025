package main
import (
  "fmt"
  "os"
  "strconv"
  "strings"
)

func run() error {
  code, err := os.ReadFile("day1.input")
  if err != nil {
    return err
  }
  
  count := 0
  acc := 50
  lines := strings.Split(string(code), "\n")
  for _, line := range lines {
    if line == "" {
      break
    }
    n, err := strconv.Atoi(line[1:])
    if err != nil {
      return err
    }
    if line[0] == 'L' {
      acc -= n
    } else if line[0] == 'R' {
      acc += n
    }
    if acc % 100 == 0 {
      count++
    }
  }

  fmt.Printf("Result: %d", count)
  return nil
}
func main() {
  if err := run(); err != nil {
    fmt.Printf("error: %s\n", err)
  }
}
