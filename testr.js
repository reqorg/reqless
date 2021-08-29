const reqless = require("./index")

const response = reqless({ 
    url: "http://info.cern.ch/",
    method: "GET"
})
console.log(response.body)