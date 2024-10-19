const mongoose = require('mongoose');
const Schema = mongoose.Schema;

const temperatureDataSchema = new Schema({
  type: { type: String, enum: ['temperature', 'temperature_color'], required: true },
  value: { type: Number, required: true },
  timestamp: { type: Number, required: true },
});

const TemperatureData = mongoose.model('TemperatureData', temperatureDataSchema);

module.exports = TemperatureData;
