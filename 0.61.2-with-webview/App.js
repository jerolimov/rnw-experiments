import React from 'react';
import {
  SafeAreaView,
  View,
  Text,
  StatusBar,
} from 'react-native';

import { WebView } from 'react-native-webview';
import MarkdownView from 'react-native-showdown';

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

        <MarkdownView
          markdown={'`MarkdownView` (which renders into an webview) works also. :+1:'}
          options={{ emoji: true }}
        />

        <Text>Below the webview</Text>

      </SafeAreaView>
    </>
  );
};
