import 'react-native-gesture-handler';
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View } from 'react-native';
import Login from './src/pages/login';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator, Header } from '@react-navigation/stack';
import Register from './src/pages/register';
import { rootStackParamList } from './src/pages/login';
import SplashScreen from './src/pages/splashScreen';
import Home from './src/pages/Home';
import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import Cars from './src/pages/Escolha';
import { MaterialIcons } from '@expo/vector-icons';

const Stack = createStackNavigator<rootStackParamList>();

const Tab = createBottomTabNavigator();

function Tabs () {
  return (
    <Tab.Navigator screenOptions={{
      headerShown: false,
      tabBarShowLabel: false,
      tabBarActiveTintColor: '#A07A28',
      tabBarInactiveTintColor: 'gray',
      tabBarStyle: {
        backgroundColor: '#fff',
        height: 70,
        borderRadius: 60,
        paddingTop: 10,
        shadowColor: '#000',
        shadowOffset: { width: 0, height: -3 },
        shadowOpacity: 0.1,
        shadowRadius: 3,
      }}}>
        <Tab.Screen name="Home" component={Home} options={{
            tabBarIcon: ({ color, size, focused }) => (
              <MaterialIcons
                name='home'
                size={30}
                color={color}
              />
            ),
          }}/>
        <Tab.Screen name="Cars" component={Cars}  options={{
            tabBarIcon: ({ color, size, focused }) => (
              <MaterialIcons
                name="directions-car"
                size={30}
                color={color}
              />
            ),
          }}/>
    </Tab.Navigator>
  );
}

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator 
        // Define a primeira tela a ser aberta
        initialRouteName="splashScreen" 
        screenOptions={{ headerShown: false }}>
        	  <Stack.Screen name="Login" component={Login} />
            <Stack.Screen name="Register" component={Register} /> 
            <Stack.Screen name="splashScreen" component={SplashScreen}/>
            <Stack.Screen name="Tabs" component={Tabs}/>
        </Stack.Navigator>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
    alignItems: 'center',
    justifyContent: 'center',
  },
});
