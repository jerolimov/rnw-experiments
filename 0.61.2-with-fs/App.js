import React from 'react';
import {
  SafeAreaView,
  ScrollView,
  View,
  Text,
  StatusBar,
} from 'react-native';

import FS from 'react-native-fs';

export default function App() {

  console.warn('FS', FS);

  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView>
        <ScrollView
          contentInsetAdjustmentBehavior="automatic"
          style={styles.scrollView}>
          <Header />
          {global.HermesInternal == null ? null : (
            <View style={styles.engine}>
              <Text style={styles.footer}>Engine: Hermes</Text>
            </View>
          )}

          <View style={{ padding: 30 }}>
          <Text>Hello! {typeof FS}</Text>
          </View>

        </ScrollView>
      </SafeAreaView>
    </>
  );
};
