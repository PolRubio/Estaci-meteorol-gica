const express = require('express')
const path = require('path');
const fs = require('fs')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  const rutaArchivo = path.join(__dirname, 'archivo.txt')
  const data = fs.readFileSync(rutaArchivo, 'utf8')
  res.send({msg: data});
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})

