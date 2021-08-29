const reqless = require("./index")
const axios = require("axios")
log = console.log

async function start() {
    const url = "http://info.cern.ch/"
    const method = "GET"

    const rql_response = reqless({ url: url, method: method }).body
    const axios_response = await axios({ url: url, method: method })
    log(axios_response.data)
}

start()