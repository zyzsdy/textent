# node text extent 

**Only for win32**

This is win32 C ++ modules on a Node.js. For calculating image height and width by using a font and font size to render the results given string.

## Getting Started

### Installation

```bash
npm install textent
```

If you want to build from source but not my pre-compiled binaries. Use:

```bash
npm install textent --build-from-source
```

### Import to your code

We recommend using TypeScript or ES2015.

```typescript
import textent from 'textent'
```

However, if you want to import in the traditional way:

```javascript
const textent = require('textent').default
```

## Quick API

```typescript
render(fontName: string, fontSize: number, destString: string): size;
```

## Contributing

### Setting up your node compile environment

1. Install VS2015 or higher version with Windows SDK.

2. Install node-gyp and node-pre-gyp

```bash
npm install -g node-gyp node-pre-gyp
```

### Prepare source code

```bash
git clone https://github.com/zyzsdy/textent.git
cd ./textent
npm install --build-from-source
```

### Doing your magic

1. Run the command below, then `build/` will be setup.

```bash
node-pre-gyp configure
```

2. Open `build/binding.sln` on Visual Studio

    `text-extent.cc` is the main module source code.

    Don't forget declare your method in index.d.ts to help editor and users know how to call your method.

### Build or run


**build**

```bash
node-pre-gyp build
```

**test**

```bash
npm test
```

## LICENSE

MIT

