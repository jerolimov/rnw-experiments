import React from 'react';
import {
  SafeAreaView,
  ScrollView,
  View,
  Text,
  StatusBar,
  requireNativeComponent,
} from 'react-native';

const Draggable = requireNativeComponent('Draggable');
const Droppable = requireNativeComponent('Droppable');

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

          <Draggable
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
          </Draggable>

          <Droppable
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
          </Droppable>

        </ScrollView>
      </SafeAreaView>
    </>
  );
};
