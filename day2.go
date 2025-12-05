package main
import (
  "fmt"
  "strings"
  "os"
)

func run() error {
  code, err := os.ReadFile("day2.sample")
  if err != nil {
    return err
  }
  for _, pair := range strings.Split(string(code), ",") {
    fmt.Printf("%s", pair)
  }
  return nil
}

func main() {
  if err := run(); err != nil {
    fmt.Printf("Err: %s\n", err)
  }
}

