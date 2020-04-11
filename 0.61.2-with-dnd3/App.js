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
            onDragStart={(event) => console.warn('onDragStart', event)}
            onDrag={(event) => console.warn('onDrag', event)}
            onDragEnd={(event) => console.warn('onDragEnd', event)}

            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drag me #1</Text>
          </Draggable>

          <Droppable
            // onMouseEnter={() => console.warn('onMouseEnter')}
            // onMouseMove={() => console.warn('onMouseMove')}
            // onMouseLeave={() => console.warn('onMouseLeave')}

            allowDrop
            onDragEnter={(event) => console.warn('onDragEnter', event.nativeEvent)}
            onDragOver={(event) => console.warn('onDragOver', event.nativeEvent)}
            onDragLeave={(event) => console.warn('onDragLeave', event.nativeEvent)}
            onDrop={(event) => {
              console.warn('onDrop', Object.keys(event).join(', '));
              console.warn('onDrop nativeEvent:', JSON.stringify(event.nativeEvent));
            }}
            onDropCompleted={(event) => console.warn('onDropCompleted', event.nativeEvent)}

            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drop here #1a</Text>
          </Droppable>

          <Droppable
            // onMouseEnter={() => console.warn('onMouseEnter')}
            // onMouseMove={() => console.warn('onMouseMove')}
            // onMouseLeave={() => console.warn('onMouseLeave')}

            allowDrop
            onDragEnter={(event) => console.warn('onDragEnter', event.nativeEvent)}
            onDragOver={(event) => console.warn('onDragOver', event.nativeEvent)}
            onDragLeave={(event) => console.warn('onDragLeave', event.nativeEvent)}
            onDrop={(event) => console.warn('onDrop', event.nativeEvent)}
            onDropCompleted={(event) => console.warn('onDropCompleted', event.nativeEvent)}

            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drop here #2b</Text>
          </Droppable>

        </ScrollView>
      </SafeAreaView>
    </>
  );
};
