import { useEffect } from "react";
import { View, Image, Text } from "react-native";
import { useNavigation } from "@react-navigation/native";
import { StackNavigationProp } from "@react-navigation/stack";
import { rootStackParamList } from "../login";
import { styles } from "./style";
import { LinearGradient } from 'expo-linear-gradient';

type splashScreenProp = StackNavigationProp<rootStackParamList, 'Login'>;

export default function splashScreen() {
    const navigation = useNavigation<splashScreenProp>();

    useEffect(() => {
        setTimeout(() => {
            navigation.replace('Login');
        }, 2000);
    } , []);

    return (
        <LinearGradient style={styles.container} colors={['#1D1F20', '#A07A28' ]}>  
            <Text style={styles.text}>ecom<Text style={styles.textCars}>Cars<Text style={styles.text}>+</Text></Text></Text> 
            <Text style={styles.text2}>by Bruno Bertussi</Text>
        </LinearGradient>
    )
}