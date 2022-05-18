This project is designed to be a cross platform NodeJS display solution that supports multiple displays.

<ul> 
  <li>Goal 1: Develop cross platform display api to query multiple physical displays</li>
  <li>Goal 2: Detect which display currently has focus</li>
  <li>Goal 3: Screen capture support for active display</li>
</ul>

## Supported Platforms
<ul>
  <li><img src='https://icons.iconarchive.com/icons/icons8/windows-8/24/Systems-Mac-Os-icon.png'> Mac OSX 10.5+</li>
  <li><img src='https://icons.iconarchive.com/icons/tatice/operating-systems/24/Windows-icon.png'> Windows 2000 or later</li>
  <li><img src='https://icons.iconarchive.com/icons/dakirby309/simply-styled/24/OS-Linux-icon.png'> Linux 2.7+ (New* Main display only)</li>
</ul>

## Requirements
Install Yarn<br/>
`npm install yarn -g`<br/><br/>
Compile<br/>
`yarn`<br/><br/>
Run Demo<br/>
`node test.js`<br/><br/>

## Usage
```
const screen = require('native-screen-js');
console.log(screen.getDisplayInfo());
```

## Output
```
{
  "displayCount": 1,
  "screens": [
    {
      "modelNumber": 43298, <--- OSX Only
      "isBuiltIn": 1,
      "isMainDisplay": 1,
      "width": 1440,
      "height": 900,
      "x": 0,  <--- Top left corner of display in virtual space
      "y": 0,  <--- Top left corner of display in virtual space
      "rotation": 0 <--- OSX Only
    }
  ]
}
```
