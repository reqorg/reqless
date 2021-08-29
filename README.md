# reqless
A Node.js HTTP client written in C++

## Installation

Using npm:

```bash
$ npm install reqless
```

## Usage
```js
const reqless = require("reqless")

const response = reqless.req("https://example.com/", "GET")
console.log(response.body)
console.log(response.headers)
```

## Response
The `req` function returns a `response` object.
A response object has the following attributes:
  - body: The body received from the HTTP request.
  - headers: The headers received from the HTTP request.
