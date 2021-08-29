const axios = require("axios")
const reqless = require("./index");

test("HTTP GET" , async () => {
    const url = "http://info.cern.ch/"
    const method = "GET"

    const rql_response = reqless({ url: url, method: method })
    const axios_response = await axios({ url: url, method: method })
    expect(rql_response.body).toBe(axios_response.data);
})

/*
test("HTTP POST with data" , async () => {
    const url = "http://httpbin.org/post"
    const method = "POST"
    const data = "reqless_is=cool"

    const rql_response = reqless({ url: url, method: method, data: data})
    console.log(rql_response.body)
    const json = JSON.parse(rql_response.body).data

    expect(json).toBe(data);
})
*/