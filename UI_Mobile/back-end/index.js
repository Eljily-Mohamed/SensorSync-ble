const express = require('express');
const mongoose = require('mongoose');
const TemperatureData = require('./models/TemperatureData'); 
const cors = require('cors');

const app = express();
const port = 3000;

app.use(cors());

// MongoDB connection
const mongoUri = 'mongodb+srv://mohamedeljily2005:sdjk3q2C0Wmai7YL@emb-ble.xawcghv.mongodb.net/temp';
mongoose.connect(mongoUri, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
});

const db = mongoose.connection;
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', async () => {
  console.log('Connected to MongoDB');
});

// Endpoint to fetch the last 7 temperature and temperature color records
app.get('/temperatures', async (req, res) => {
  try {
    const temperatureData = await TemperatureData.find({
      $or: [
        { type: 'temperature' },
        { type: 'temperature_color' }
      ]
    }).sort({ timestamp: -1 }).limit(18);

    res.json(temperatureData);
  } catch (error) {
    res.status(500).send(error);
  }
});

app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});