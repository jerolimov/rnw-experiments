import React from 'react';
import {
  SafeAreaView,
  StyleSheet,
  ScrollView,
  View,
  Text,
  StatusBar,
  Button,
} from 'react-native';

import { DocumentDirectoryPath, downloadFile } from 'react-native-fs';

export default function App() {
  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView>
        <ScrollView
          contentInsetAdjustmentBehavior="automatic"
          style={styles.scrollView}>
          {global.HermesInternal == null ? null : (
            <View style={styles.engine}>
              <Text style={styles.footer}>Engine: Hermes</Text>
            </View>
          )}
          <Text>
            DocumentDirectoryPath = {DocumentDirectoryPath}
          </Text>
          <Button
            title="Download"
            onPress={() => downloadFile({ fromUrl: 'https://www.google.de/' })}
          />
        </ScrollView>
      </SafeAreaView>
    </>
  );
};

const styles = StyleSheet.create({
  scrollView: {
    backgroundColor: Colors.lighter,
    padding: 40,
    margin: 40,
  },
  engine: {
    position: 'absolute',
    right: 0,
  },
});
