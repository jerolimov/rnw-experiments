/**
 * @format
 * @flow
 */

import React, { Fragment } from 'react';
import { SafeAreaView, ScrollView, View, Text, StatusBar, TouchableOpacity } from 'react-native';

export default function App() {
  console.warn('App')
  return (
    <Fragment>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView>
        <ScrollView contentInsetAdjustmentBehavior="automatic">
          {global.HermesInternal == null ? null : (
            <View>
              <Text>Engine: Hermes</Text>
            </View>
          )}
          <View style={{ paddingTop: 50 }}>
            <Text>Hallo</Text>
          </View>

          <View style={{ paddingTop: 50 }}>
            <Text>Hallo2</Text>
          </View>

          <View
            enableFocusRing
            acceptsKeyboardFocus
            allowDrag
            allowDrop
            draggable

            onPress={() => console.warn('onPress')}
            onClick={() => console.warn('onClick')}

            onDragStart={() => console.warn('onDragStart')}
            onDrag={() => console.warn('onDrag')}
            onDragEnd={() => console.warn('onDragEnd')}

            onDragEnter={() => console.warn('onDragEnter')}
            onDragOver={() => console.warn('onDragOver')}
            onDragLeave={() => console.warn('onDragLeave')}

            onDrop={() => console.warn('onDrop')}

            onMouseEnter={() => console.info('onMouseEnter')}
            onMouseLeave={() => console.info('onMouseLeave')}

            topMouseEnter={() => console.info('topMouseEnter')}
            topMouseLeave={() => console.info('topMouseLeave')}

            style={{ borderWidth: 2, borderColor: 'red', padding: 50 }}
          >
            <Text onDragOver={() => console.warn('onDragOver 4')}>Hello</Text>
          </View>

        </ScrollView>
      </SafeAreaView>
    </Fragment>
  );
};
