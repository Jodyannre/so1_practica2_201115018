import React, { useState,useEffect } from "react";
import axios from "axios";
import '../styles/styles.css'
import Table from 'react-bootstrap/Table'
import Children from './ChildrenTable'


export default function RAM() {
  const [datos, setDatos] = useState([])

  const getDataCPU = async () => {
    const res = await axios.get(`http://${global.ip}:5000/getDataCPU`);
    //const texto = JSON.stringify(res.data)
    setDatos(res.data)
    //console.log(texto)
    //console.log(datos)
  }

  useEffect(()=>{
    const interval = setInterval(()=>{
      getDataCPU();
    }, 2000)
    getDataCPU();
  },[]);

  //Tabla de resultados
  const data= [{memoria:"Joel Rodriguez", pid:25,nombre:"Estudiante",usuario:"otro val"}]
  const dataChildren= [{nombre:"no tiene",pid:-1}]
  const headers = [{name:"nombre",age:"edad",profession:"otro", children:"otro"}]
  return (
        <>
            <div style={{hposition:"relative",marginBottom:"1%",padding:"1%",
            backgroundColor :"white"}}>
            <h1>Modulo CPU</h1>  
            </div>     
        <div className="App" style={{overflow: "scroll", height:"800px"}}>  

            <Table striped bordered hover >
                <thead>
                <tr>
                    <th>Memoria</th>
                    <th>PID</th>
                    <th>Nombre</th>
                    <th>Usuario</th>
                    <th>Hijos</th>    
                </tr>  
                </thead>
                <tbody>
                    {datos.map((val,key)=>{
                        return(
                        <tr key={key}>
                            <td>{val.memoria}</td>
                            <td>{val.pid}</td>
                            <td>{val.nombre}</td>
                            <td>{val.usuario}</td>
                            <td><Children
                            datos={val.hijos ? val.hijos: dataChildren}
                            /></td>
                        </tr>
                        )
                    })}
                </tbody>              
            </Table>
        </div>
        </>
  )
}
