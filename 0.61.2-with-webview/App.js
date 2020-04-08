import React from 'react';
import {
  SafeAreaView,
  View,
  Text,
  StatusBar,
} from 'react-native';

import { WebView } from 'react-native-webview';

export default function App() {
  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView style={{ flex: 1 }}>

        {global.HermesInternal == null ? null : (
          <View style={styles.engine}>
            <Text style={styles.footer}>Engine: Hermes</Text>
          </View>
        )}

        <Text>Above the webview</Text>

        <WebView
          source={{ html: 'hello world'}}
        />

        <Text>Below the webview</Text>

      </SafeAreaView>
    </>
  );
};
