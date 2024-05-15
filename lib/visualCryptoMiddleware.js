const { execFile } = require('child_process');
const fs = require('fs').promises;
const path = require('path');

module.exports = function() {
    return async function(req, res, next) {
        const inputFilename = 'input.txt';
        const outputBase = 'output';
        const responseFilename = 'response.txt';

        try {
            // Write the request data to 'input.txt'
            const requestData = JSON.stringify(req.body);
            await fs.writeFile(inputFilename, requestData);

            // Encrypt the data
            await execPromise('./bin/vcrypt', ['encrypt', inputFilename, outputBase]);

            // Decrypt the data
            await execPromise('./bin/vcrypt', ['decrypt', outputBase, responseFilename]);

            // Check if 'response.txt' exists, create it if not
            try {
                await fs.access(responseFilename);
            } catch {
                // If 'response.txt' doesn't exist, create an empty file
                await fs.writeFile(responseFilename, '');
            }

            // Read the decrypted data from 'response.txt'
            const response = await fs.readFile(responseFilename, 'utf8');
            res.send(response);
        } catch (error) {
            console.error('Error in visual cryptography middleware:', error);
            next(error);
        }
    };
};

function execPromise(command, args) {
    return new Promise((resolve, reject) => {
        execFile(command, args, (error, stdout, stderr) => {
            if (error) {
                reject(new Error(stderr || error));
            } else {
                resolve(stdout);
            }
        });
    });
}
