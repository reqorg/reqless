const fs = require('fs');
let file = "./index.html" , dir = "./build";


let rm_file = () => {
    fs.unlink(file , (err) =>{
        if(err) console.log(err);
    })    
}

let rm_dir = () => {
    if(fs.existsSync(dir)){
        fs.rmdir(dir, { recursive: true }, (err) => {
            if (err) {
                throw err;
            }
        });
    }
}

if (fs.existsSync(file)) rm_file();
else if (fs.existsSync(dir)) rm_dir();


const { execFileSync } = require("child_process");
const reqless = require('./index');

execFileSync('wget', ['http://info.cern.ch/']);

const read_file = fs.readFileSync('./index.html' , {encoding : 'utf-8'});
    const response =  reqless({ 
        url: "http://info.cern.ch/",
        method: "GET"
    })

test("reqless test" , () => {
    expect(response.body.trim()).toBe(read_file.trim());
})

fs.unlink(file , (err) =>{
    if(err) console.log(err);
})

fs.rm(dir, { recursive: true }, (err) => {
    if (err) { throw err;}
});
