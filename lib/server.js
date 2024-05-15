const express = require('express');
const app = express();
const visualCryptoMiddleware = require('./visualCryptoMiddleware'); // Path to your middleware file

app.use(express.json());
app.post('/test', visualCryptoMiddleware(), (req, res) => {
    
});

// Start the server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});
