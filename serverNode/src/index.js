const express = require("express")
const cors = require("cors")
const app = express()
const PORT = 5000
const mysql = require("mysql")
const { response } = require("express")
const ip = "34.125.57.219"
app.use(cors())


const conexion = mysql.createConnection({
    host: "35.238.86.126",
    user: "joddie",
    password: "1.,I}q>DPOLd(d#(",
    database: "tarea2"
})


app.use(express.urlencoded({extended:true}))
app.use(express.json())

app.get("/", (req,res)=>{
    res.json({msj: "Hola mundo"})
})

app.get("/getDataRAM",(req,res)=>{
    let query = "SELECT * FROM RAM ORDER BY id DESC LIMIT 1"
    conexion.query(query,function(err,result){
        if(err){
            res.sendStatus(502)
        }else{
            res.send(result[0].info)
        }
    })
})


app.get("/getDataCPU",(req,res)=>{
    let query = "SELECT * FROM CPPU ORDER BY id DESC LIMIT 1"
    conexion.query(query,function(err,result){
        if(err){
            res.sendStatus(502)
        }else{
            res.send(result[0].info)
        }
    })
})

app.listen(PORT, ()=>{
    console.log(`Servidor escuchando en el puerto: ${PORT}`)
})