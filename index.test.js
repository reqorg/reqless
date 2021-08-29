const axios = require("axios")
const reqless = require("./index");

const url = "http://info.cern.ch/"
const method = "GET"

test("HTTP GET" , async () => {
    const rql_response = reqless({ url: url, method: method })
    const axios_response = await axios({ url: url, method: method })
    expect(rql_response.body).toBe(axios_response.data);
})