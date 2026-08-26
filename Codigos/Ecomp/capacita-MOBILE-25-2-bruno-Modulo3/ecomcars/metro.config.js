const { getDefaultConfig } = require('expo/metro-config');

const config = getDefaultConfig(__dirname);

config.resolver.sourceExts.push('ts', 'tsx', 'js', 'jsx', 'json', 'wasm', 'svg');

config.resolver.assetExts = config.resolver.assetExts.filter((ext) => ext !== 'svg');

module.exports = config;