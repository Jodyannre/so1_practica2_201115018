package main

import (
	"database/sql"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os/exec"

	_ "github.com/go-sql-driver/mysql"
	"github.com/gorilla/mux"
	"github.com/jasonlvhit/gocron"
)

var puerto int = 4000
var port = fmt.Sprintf(":%d", puerto)
var tiempoHilo uint64 = 20

type RAM struct {
	Total int `json:"total"`
	Free  int `json:"free"`
	Used  int `json:"used"`
}

type CPU struct {
}

/*
type ramConsulta struct {
	Id   int
	Info string
}
*/

func main() {

	go fmt.Println("Server running at port ", port)
	go hilo()
	router := mux.NewRouter()
	router.HandleFunc("/", hello)
	err := http.ListenAndServe(port, router)
	if err != nil {
		log.Fatal(err)
	}
}

func enviarDataRam(db *sql.DB) {
	datos := getDataRam()
	query := fmt.Sprintf("INSERT INTO RAM (info) VALUES ('%s')", string(datos))
	fmt.Println(query)
	db.Query(query)
	println("Datos de ram enviados a la db")
}

func enviarDataCpu(db *sql.DB) {
	datos := getDataCpu()
	query := fmt.Sprintf("INSERT INTO CPPU (info) VALUES ('%s')", string(datos))
	//fmt.Println(query)
	db.Query(query)
	println("Datos de cpu enviados a la db")
}

func enviarDatos() {
	db, err := sql.Open("mysql", "joddie:1.,I}q>DPOLd(d#(@tcp(35.238.86.126)/tarea2")
	if err != nil {
		fmt.Println("Error")
		fmt.Println(err)
	}
	enviarDataRam(db)
	enviarDataCpu(db)
	defer db.Close()
}

func getDataRam() []byte {
	nRam := RAM{}
	cmd := exec.Command("sh", "-c", "cat /proc/ram_201115018")
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(err)
	}
	json.Unmarshal(out, &nRam)
	var total, free, used int
	total = nRam.Total
	free = nRam.Free
	used = nRam.Used
	nRam.Total = 100
	nRam.Free = (free * 100) / total
	nRam.Used = (used * 100) / total
	data, err2 := json.Marshal(nRam)
	if err2 != nil {
		fmt.Println(err)
	}
	return data
}

func getDataCpu() []byte {
	cmd := exec.Command("sh", "-c", "cat /proc/cpu_201115018")
	out, err := cmd.CombinedOutput()
	if err != nil {
		fmt.Println(err)
	}
	/*
		output := string(out[:])
		fmt.Println(output)
	*/
	//Escribir archivo

	//Escribir archivo de texto
	/*
		f, err2 := os.Create("data.txt")
		if err2 != nil {
			log.Fatal(err2)
		}
		defer f.Close()

		_, err3 := f.Write(out)

		if err3 != nil {
			log.Fatal(err2)
		}
	*/
	return out
}

func getDataCPUusage() {

}

func enableCors(w *http.ResponseWriter) {
	(*w).Header().Set("Access-Control-Allow-Origin", "*")
}

func hello(res http.ResponseWriter, req *http.Request) {
	fmt.Fprintf(res, "Hola mundo")
}

func hilo() {
	gocron.Every(tiempoHilo).Second().Do(enviarDatos)
	<-gocron.Start()
}
