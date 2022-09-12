import React, { useState,useEffect } from "react";
import axios from "axios";
import { Chart as ChartJS, ArcElement, Tooltip, Legend } from 'chart.js';
import { Doughnut } from 'react-chartjs-2';
import {Card,Button} from 'react-bootstrap'


ChartJS.register(ArcElement, Tooltip, Legend);


export default function RAM() {
  const [datos, setDatos] = useState([])

  const getDataRAM = async () => {
    const res = await axios.get(`http://${global.ip}:5000/getDataRAM`);
    //const texto = JSON.stringify(res.data)
    setDatos(res.data)
    //console.log(texto)
    //console.log(datos)
  }

  useEffect(()=>{
    const interval = setInterval(()=>{
      getDataRAM();
    }, 20000)
    getDataRAM();
  },[]);

  //Tabla de resultados
  const data = {
    labels: ['Free', 'Used'],
    datasets: [
      {
        label: '# of Votes',
        data: [datos.free,datos.used],
        backgroundColor: [
          'rgba(255, 99, 132, 0.2)',
          'rgba(54, 162, 235, 0.2)',
          'rgba(255, 206, 86, 0.2)',
          'rgba(75, 192, 192, 0.2)',
          'rgba(153, 102, 255, 0.2)',
          'rgba(255, 159, 64, 0.2)',
        ],
        borderColor: [
          'rgba(255, 99, 132, 1)',
          'rgba(54, 162, 235, 1)',
          'rgba(255, 206, 86, 1)',
          'rgba(75, 192, 192, 1)',
          'rgba(153, 102, 255, 1)',
          'rgba(255, 159, 64, 1)',
        ],
        borderWidth: 1,
      },
    ],
  };
  return (
    <>  
      <div style={{hposition:"relative",marginBottom:"1%",padding:"1%",
        backgroundColor :"white"}}>
        <h1>Modulo RAM</h1>  
        </div>          
        <div style={{height:"60vh",position:"relative",marginBottom:"1%",padding:"1%",
        backgroundColor :"white", border:"4px dotted blue"}}>
          <Doughnut data={data}options={{maintainAspectRatio:false}} />
        </div>
        </>

  )
}
