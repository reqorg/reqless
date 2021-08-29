# reqless
A Node.js HTTP client written in C++, with focus on performance, reliability and safety.

## Installation

Using npm:

```bash
$ npm install reqless
```

## Usage
```js
const reqless = require("reqless")

const response = reqless({ 
    url: "http://info.cern.ch/",
    method: "GET"
})
console.log(response.body, response.headers);
```

## Response
The `req` function returns a `response` object.
A response object has the following attributes:
  - body: The body received from the HTTP request.
  - headers: The headers received from the HTTP request.
