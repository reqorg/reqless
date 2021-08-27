const express = require('express')
const app = express()
const port = 3000
log = console.log

app.get('/', (req, res) => {
    log(req)
    res.send('Hello World!')
})

app.listen(port, () => {
    console.log(`Test server listening at http://localhost:${port}`)
})