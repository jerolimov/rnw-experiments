import React, { useState } from 'react';
import {
  SafeAreaView,
  ScrollView,
  View,
  Text,
  StatusBar,
  requireNativeComponent,
  TouchableWithoutFeedback,
  TouchableOpacity,
} from 'react-native';

const Draggable = requireNativeComponent('Draggable');
const Droppable = requireNativeComponent('Droppable');

function createInitialState() {
  const result = [];

  for (let a = 0; a < 10; a++) {
    result[a] = [];
    for (let b = 0; b < 10; b++) {
      result[a][b] = a + b;
    }
  }
  return result;
}

console.log(createInitialState())

export default function App() {
  const [numbers, forceUpdate] = useState(createInitialState)

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

          <View style={{ margin: 30 }}>
            {
              numbers.map((_, a) => (
                <View key={a} style={{ flexDirection: 'row' }}>
                  {
                    numbers.map((_, b) => (
                      <Box key={b} a={a} b={b} content={numbers[a][b]} />
                    ))
                  }
                </View>
              ))
            }
          </View>

          <Draggable
            // onMouseEnter={() => console.warn('onMouseEnter')}
            // onMouseMove={() => console.warn('onMouseMove')}
            // onMouseLeave={() => console.warn('onMouseLeave')}

            allowDrag
            onDragStart={(event) => console.warn('onDragStart', event)}
            onDragStarting={(event) => console.warn('onDragStarting', event)}
            onDropCompleted={(event) => console.warn('onDropCompleted', event.nativeEvent)}
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
            onDrop={(event) => {
              console.warn('onDrop', Object.keys(event).join(', '));
              console.warn('onDrop nativeEvent:', JSON.stringify(event.nativeEvent));
            }}
            style={{ padding: 30, margin: 30, borderWidth: 2, borderColor: 'red', backgroundColor: '#e0e0e0' }}
          >
            <Text>Drop here #2b</Text>
          </Droppable>

        </ScrollView>
      </SafeAreaView>
    </>
  );
};

function Box({ a, b, content }) {
  const [selected, setSelected] = useState(false)

  const size = 70;
  const backgroundColor = selected ? '#bbdefb' : 'transparent';
  const borderColor = 'gray';

  const allowDrag = content > 0;
  const allowDrop = content < 10;

  return (
    <Droppable>
      <TouchableOpacity
        onPress={() => console.warn('onPress inner')}
        style={{ width: size, height: size, borderWidth: 1, borderColor, backgroundColor }}
      >
        <Text>{a},{b} = {content}</Text>
        <Text>drag={allowDrag ? 'true' : 'false'}</Text>
        <Text>drop={allowDrop ? 'true' : 'false'}</Text>
      </TouchableOpacity>
    </Droppable>
  )

}
