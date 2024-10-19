import React, { useEffect, useState } from 'react';
import { View, Text, StyleSheet, Dimensions, ScrollView } from 'react-native';
import { LineChart } from 'react-native-chart-kit';

const Home = () => {
  const [temperatureData, setTemperatureData] = useState([]);
  const [kelvinData, setKelvinData] = useState([]);
  const [error, setError] = useState(null);

  useEffect(() => {
    const interval = setInterval(() => {
      fetchData();
    }, 1000); // Fetch data every second

    // Cleanup function to clear interval when component unmounts
    return () => clearInterval(interval);
  }, []);

  const fetchData = async () => {
    try {
      const response = await fetch('https://server-ble-1.onrender.com/temperatures'); // Updated URL for deployed server
      if (!response.ok) {
        throw new Error('Network response was not ok');
      }
      const data = await response.json();
      // Filter temperature and temperature color data
      const temperatureValues = data.filter(item => item.type === 'temperature').map(item => item.value);
      const kelvinValues = data.filter(item => item.type === 'temperature_color').map(item => item.value);
      // Keep only the last 12 values
      const last12Temperature = temperatureValues.slice(-12);
      const last12Kelvin = kelvinValues.slice(-12);
      // Update state
      setTemperatureData(last12Temperature);
      setKelvinData(last12Kelvin);
      setError(null); // Reset error state
    } catch (error) {
      console.error('Error fetching data:', error.message);
      setError(error.message); // Set error state for display
    }
  };

  // Function to generate labels for seconds
  const generateSecondLabels = () => {
    const labels = [];
    const now = new Date();
    for (let i = 11; i >= 0; i--) {
      const seconds = now.getSeconds() - i;
      labels.push(seconds < 10 ? `0${seconds}` : `${seconds}`);
    }
    return labels;
  };

  return (
    <ScrollView style={styles.container}>
      <View style={styles.header}>
        <Text style={styles.title}>EMB BLE</Text>
      </View>
      {error && <Text style={styles.errorText}>ERROR: {error}</Text>}
      <View style={styles.chartContainer}>
        <Text style={styles.chartTitle}>Temperature</Text>
        <LineChart
          data={{
            labels: generateSecondLabels(),
            datasets: [{
              data: temperatureData,
              strokeWidth: 2,
              color: (opacity = 1) => `rgba(255, 0, 0, ${opacity})`, // Red color for temperature chart
              bezier: false,
            }],
          }}
          width={Dimensions.get('window').width - 20}
          height={220}
          yAxisSuffix="°C"
          yAxisInterval={1}
          yAxisMin={0}
          yAxisMax={60}
          fromZero
          chartConfig={{
            backgroundColor: '#9333ff ',
            backgroundGradientFrom: '#1E2923',
            backgroundGradientTo: '#08130D',
            decimalPlaces: 1,
            color: (opacity = 1) => `rgba(26, 255, 146, ${opacity})`,
            labelColor: (opacity = 1) => `rgba(255, 255, 255, ${opacity})`,
            style: {
              borderRadius: 16,
            },
            propsForBackgroundLines: {
              strokeWidth: 1,
              stroke: '#2c2c2c',
            },
            propsForLabels: {
              fontSize: 10,
              fontFamily: 'Helvetica',
            },
          }}
          style={styles.chart}
        />
      </View>
      <View style={styles.chartContainer}>
        <Text style={styles.chartTitle}>Temperature Color </Text>
        <LineChart
          data={{
            labels: generateSecondLabels(),
            datasets: [{
              data: kelvinData,
              strokeWidth: 2,
              color: (opacity = 1) => `rgba(0, 0, 255, ${opacity})`, // Blue color for kelvin chart
              bezier: false,
            }],
          }}
          width={Dimensions.get('window').width - 20}
          height={220}
          yAxisSuffix="K"
          fromZero
          chartConfig={{
            backgroundColor: '#022173',
            backgroundGradientFrom: '#1E2923',
            backgroundGradientTo: '#08130D',
            decimalPlaces: 1,
            color: (opacity = 1) => `rgba(26, 255, 146, ${opacity})`,
            labelColor: (opacity = 1) => `rgba(255, 255, 255, ${opacity})`,
            style: {
              borderRadius: 16,
            },
            propsForBackgroundLines: {
              strokeWidth: 1,
              stroke: '#2c2c2c',
            },
            propsForLabels: {
              fontSize: 10,
              fontFamily: 'Helvetica',
            },
          }}
          style={styles.chart}
        />
      </View>
      <View style={styles.footer}>
        <Text style={styles.footerText}>Powered by EMB BLE</Text>
      </View>
    </ScrollView>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
  },
  header: {
    padding: 20,
    borderBottomWidth: 1,
    borderBottomColor: '#ccc',
    alignItems: 'center',
    backgroundColor: '#33acff',
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    color: '#fff',
  },
  errorText: {
    color: 'red',
    textAlign: 'center',
    marginTop: 10,
  },
  chartContainer: {
    marginVertical: 10,
    alignItems: 'center',
  },
  chartTitle: {
    fontSize: 18,
    marginBottom: 10,
    color: '#000',
  },
  chart: {
    marginVertical: 8,
    borderRadius: 16,
  },
  footer: {
    padding: 10,
    borderTopWidth: 1,
    borderTopColor: '#ccc',
    alignItems: 'center',
    backgroundColor: '#fff',
  },
  footerText: {
    fontSize: 14,
    color: '#000',
  },
});

export default Home;
