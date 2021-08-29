const reqless = require("./index")

const response = reqless({ 
    url: "https://example.com/",
    method: "GET"
})
console.log(response.headers)