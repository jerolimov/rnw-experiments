import React from 'react';
import {
  SafeAreaView,
  ScrollView,
  View,
  Text,
  StatusBar,
  requireNativeComponent,
} from 'react-native';

const Dragable = requireNativeComponent('Dragable');
const Dropable = requireNativeComponent('Dropable');

export default function App() {
  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView style={{ flex: 1 }}>
        <ScrollView contentInsetAdjustmentBehavior="automatic">

          {global.HermesInternal == null ? null : (
            <View style={styles.engine}>
              <Text style={styles.footer}>Engine: Hermes</Text>
            </View>
          )}

          <Dragable
            // onMouseEnter={() => console.warn('onMouseEnter')}
            // onMouseMove={() => console.warn('onMouseMove')}
            // onMouseLeave={() => console.warn('onMouseLeave')}

            allowDrag
            onDragStart={() => console.warn('onDragStart')}
            onDrag={() => console.warn('onDrag')}
            onDragEnd={() => console.warn('onDragEnd')}

            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drag me #1</Text>
          </Dragable>

          <Dropable
            // onMouseEnter={() => console.warn('onMouseEnter')}
            // onMouseMove={() => console.warn('onMouseMove')}
            // onMouseLeave={() => console.warn('onMouseLeave')}

            allowDrop
            onDragEnter={() => console.warn('onDragEnter')}
            onDragOver={() => console.warn('onDragOver')}
            onDragLeave={() => console.warn('onDragLeave')}
            onDrop={() => console.warn('onDrop')}
            onDropCompleted={() => console.warn('onDropCompleted')}

            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drop here #1</Text>
          </Dropable>

        </ScrollView>
      </SafeAreaView>
    </>
  );
};
