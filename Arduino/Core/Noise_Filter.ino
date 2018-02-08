/*
 * Noise_Filter
 * 
 * Removes noise from data using a simple linear recursive exponential filter.
 * 
 * Created by Arend-Jan Hengst, RMSG, 12-11-2017
 * 
 * Source: https://www.megunolink.com/documentation/arduino-libraries/exponential-filter/
 */

// define the weight of new values, a value in the range [0, 1]
// higher values make the filter respond faster to changes, but reduces the smoothing.
float weight = 0.6;

/*
 * noiseFilter
 * 
 * Filters noise based on previous data.
 * Using this formula:
 * yn = w * xn + (1 - w) * yn-1
 * Where:
 * yn: filtered value at n
 * w: weight factor of a new value
 * xn: new value
 * yn-1: previous filtered value
 * 
 * float newValue       the new value
 * float smoothedValue  the current smoothed value
 * 
 * return float smoothed value
 */
float noiseFilter (float newValue, float oldSmoothedValue) {
  return weight * newValue + (1 - weight) * oldSmoothedValue;
}

